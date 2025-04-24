package Koha::Plugin::PifPafPlug::SearchFromList;

## It's good practive to use Modern::Perl
use Modern::Perl;
## Required for all plugins
use base qw( Koha::Plugins::Base );

## We will also need to include any Koha libraries we want to access
use CGI qw( -utf8 );
use C4::Search qw( SimpleSearch );
use Koha::SearchEngine::Search;
use Spreadsheet::Read qw( ReadData rows parses );
use Spreadsheet::ReadSXC qw( read_sxc );
use Mojo::JSON qw( decode_json encode_json );
use C4::Biblio qw( TransformMarcToKoha );
use Unicode::Normalize;

## Here we set our plugin version
our $VERSION = '1.2';

## Here is our metadata, some keys are required, some are optional
our $metadata = {
    name   => 'SearchFromList',
    author => 'Olivier Crouzet',
    description => 'upload a list of documents and launch an automatic search in the library catalog',
    date_authored   => '2025-01-21',
    date_updated    => '2025-01-23',
    minimum_version => '22.11',
    maximum_version => undef,
    version         => $VERSION,
};

## This is the minimum code required for a plugin's 'new' method
## More can be added, but none should be removed
sub new {
    my ( $class, $args ) = @_;

    ## We need to add our metadata here so our base class can access it
    $args->{'metadata'} = $metadata;
    $args->{'metadata'}->{'class'} = $class;

    ## Here, we call the 'new' method for our base class
    ## This runs some additional magic and checking
    ## and returns our actual $self
    my $self = $class->SUPER::new($args);
    return $self;

}

sub tool {
    my ( $self, $args ) = @_;

    my $cgi = $self->{'cgi'};

    if ($cgi->param('uploadfile')) {
        $self->extract_content();
    } else {
        my $template = $self->get_template({ file => 'tool.tt' });
        my $cfg = decode_json($self->retrieve_data('cfg')); 
        $template->param( 'alterlabel' => $cfg->{'alterlabel'}, 'error' => $cgi->param('error'));
        $self->output_html( $template->output() );

    }
}

sub configure {
    my ( $self , $args ) = @_;
    my $cgi = $self->{'cgi'};
    
    my @fields = qw/isbn issn alterid title author publisher pubdate alterlabel/;

    # Save config in database
    if ( $cgi->param('saveconfig') ) {
        
        my $cfg;
        for (@fields) {
            $cfg->{$_} = $cgi->param($_);
        }

        my $json = encode_json($cfg);
        $self->store_data({ cfg => $json });
    }

    my $template = $self->get_template({ file => 'configure.tt' });

    my $cfg = decode_json($self->retrieve_data('cfg')); 
    for (@fields) {
        $template->param($_ => $cfg->{$_});
    }

    $self->output_html( $template->output() );
}

sub extract_content {
    my ( $self ) = @_;
    my $cgi = $self->{'cgi'};

    my $filename = $cgi->param('uploadfile');
    my %valid_mimetypes = ( 
            'application/octet-stream' => 'csv',
            'text/csv' => 'csv',
            'text/plain' => 'csv',
            'application/vnd.ms-excel' => 'xls',
            'application/vnd.openxmlformats-officedocument.spreadsheetml.sheet' => 'xlsx',
            'application/vnd.oasis.opendocument.spreadsheet' => 'ods',
            );

    my $mimetype = $cgi->uploadInfo($filename)->{'Content-Type'};
    my $parser = $valid_mimetypes{$mimetype};
    my $upload = $cgi->upload('uploadfile');
    my $tmpfile = $cgi->tmpFileName($filename);

    my $error = !$parser ? 'badformat' : -z $upload ? 'empty' : '';
    if ( $error ) {
        print $cgi->redirect("/cgi-bin/koha/plugins/run.pl?class=Koha::Plugin::PifPafPlug::SearchFromList&method=tool&error=$error");
        return;
    }

    my $workbook;
    my $sheet;
    # The leading spaces must be removed so as not to compromise search. read_sxc do it by default. ReadData with the "strip" option set to 1.
    if ( $parser eq 'ods' ) {
        $workbook  = read_sxc($tmpfile, {OrderBySheet => 1}); 
        $sheet = $workbook->[0]->{data};
        $self->parse_content($sheet);
    } else {
        $workbook  = ReadData ($tmpfile, parser => $parser, strip => 1);

        if ( defined($workbook->[0]{error}) ) {
            print $cgi->redirect("/cgi-bin/koha/plugins/run.pl?class=Koha::Plugin::PifPafPlug::SearchFromList&method=tool&error=badformat");
            return;
        }

        $sheet = $workbook->[1];
        my @rows = rows($sheet);
        $self->parse_content(\@rows);
    }
}

sub parse_content {
    my ( $self, $content ) = @_;
    my $cgi = $self->{'cgi'};

    # find which ones among main keys have been choosen
    my $searchkeys;
    my @mainkeys;
    my $params = $cgi->Vars;
    foreach ('isbn','issn','alterid','title','author','publisher','pubdate') {
        if ( $params->{$_} ) {
            $searchkeys->{$_} = $params->{$_};
            push @mainkeys, $_ if $_ !~ /author|pub/; # searchkeys pushed in separated array to keep fixed order : isbn first and so on.
        }
    }

    # detect the type of reference to columns that has been used
    my $type;
    my @filecolumns = values %$searchkeys;
    if ( $filecolumns[0] !~ /[A-Za-z]/ ) { 
        $type = 'numbers';
    # FIXME not perfect method to be sure that it's not headers even if that statistically leaves very few chance.
    } elsif ( $filecolumns[0] =~/^([A-Z]{1,2}|[a-z]{1,2})$/ and (length "@filecolumns") - $#filecolumns <= scalar @filecolumns * 2 ) {
        $type = "letters";
    } else {
        $type = "headers";
    }

    # convert columns names to array indexes
    my $colnumbers;
    if ($type eq 'headers') {
        my ($firstline) = shift @$content;
        my @headers = map { s/\s+$//; lc $self->unaccent($_) } @$firstline;
        my %indexes;
        @indexes{@headers} = 0..$#headers; 
        foreach (keys %$searchkeys) {
            $colnumbers->{$_} = $indexes{lc $self->unaccent($searchkeys->{$_})};
        }
    } else {
        while (my ($key, $value) = each %$searchkeys) {
            $colnumbers->{$key} = $type eq 'numbers' ? $value - 1 : $self->letter2number($value);
        }
    }

    my $searchengine = C4::Context->preference('SearchEngine');

    my $found;
    my $notfound;
    my $cfg = decode_json($self->retrieve_data('cfg')); 
    foreach my $row (@$content) {
        my ( $error, $marcresults, $total_hits, $query );

        foreach my $fieldname (@mainkeys) {
            my $datafield = $row->[$colnumbers->{$fieldname}];
            next unless $datafield;
            $query = $cfg->{$fieldname}."=".$datafield;
            if ($fieldname eq 'title') {
                foreach ('author','publisher','pubdate') {
                    $query .= " AND ".$cfg->{$_}."=".$row->[$colnumbers->{$_}] if ( exists($colnumbers->{$_}) and $row->[$colnumbers->{$_}] );
                }
            } else {
                $query =~ s/[,;\/|]/ /; # When 2 identifiers in same data field concatenated by these characters, search engine would not work.
            }

            if ($searchengine eq 'Zebra') {
                ($error, $marcresults, $total_hits) = SimpleSearch($query);
            } else {
                # ElasticSearch
                my $searcher = Koha::SearchEngine::Search->new({index => $Koha::SearchEngine::BIBLIOS_INDEX});
                ( $error, $marcresults, $total_hits ) = $searcher->simple_search_compat($query);
            }

            if ( $total_hits and $total_hits == 1 ) {
                my $record = TransformMarcToKoha({ record => $marcresults->[0] });
                $record->{'match'} = $fieldname eq 'alterid' ? $cfg->{'alterlabel'} : $fieldname;
                $record->{'alterid'} = $row->[$colnumbers->{'alterid'}] if $colnumbers->{'alterid'};
                $record->{'searchedtitle'} = $row->[$colnumbers->{'title'}] if $row->[$colnumbers->{'title'}] and $fieldname eq 'title';
                push @$found, $record;
                last;
            }
        }

        if ($total_hits != 1) {
            my $unknown;
            while (my($fieldname,$colnumber) = each %$colnumbers) {
                $unknown->{$fieldname} = $row->[$colnumber];
            }
            push @$notfound, $unknown;
        }
    }

    $self->display_results($found, $notfound, $cfg->{alterlabel});
}

sub display_results {
    my ( $self, $found, $notfound, $alterlabel ) = @_;

    my $template = $self->get_template({ file => 'display_results.tt' });
    $template->param(
        foundloop     => $found,
        notfoundloop  => $notfound,
        alterlabel    => $alterlabel, 
    );

    $self->output_html( $template->output() );
}

sub letter2number {
    my ( $self, $column ) = @_;
    my $number = 0;
    for my $char (split //, uc $column) {
        $number = $number * 26 + (ord($char) - ord('A') + 1);
    }
    return $number - 1;
}

sub unaccent {
    my ( $self, $string ) = @_;
    my $decomposed = NFKD( $string );
    $decomposed =~ s/\p{NonspacingMark}//g;
    return $decomposed;
}

sub install() {
    my ( $self, $args ) = @_;

    my $cfg = {
       'isbn'      => 'ISBN',
       'issn'      => 'ISSN',
       'alterid'   => 'Identifier-standard',
       'title'     => 'Title-cover',
       'author'    => 'Author',
       'publisher' => 'Publisher',
       'pubdate'   => 'Date-of-publication',
       'alterlabel' => 'Alter id',
    };

    my $json = encode_json($cfg);
    $self->store_data({ cfg => $json });
    return 1;
}

sub uninstall() {
    my ( $self, $args ) = @_;

    C4::Context->dbh->do("delete from plugin_data where plugin_class='Koha::Plugin::PifPafPlug::SearchFromList");
    return 1;
}

1;

