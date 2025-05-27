<div id="breadcrumbs"><a href="/cgi-bin/koha/mainpage.pl">Home</a> &rsaquo; <a href="/cgi-bin/koha/plugins/plugins-home.pl">Plugins</a> &rsaquo; Search from list</div>

<div class="main container-fluid">
    <div class="row">
        <div class="col-sm-10 col-sm-push-2">
        <div id="toolbar" class="btn-toolbar">
             <div class="btn-group"><a id="searchlist" class="btn btn-default" href="/cgi-bin/koha/plugins/run.pl?class=[% CLASS %]&method=[% METHOD %]"><i class="fa fa-plus"></i> New search</a></div>
        </div>
            <h2> Search results <span>[source file: <i>[% filename %]</i>]</span></h2>

            [% WRAPPER tabs %]

                [% WRAPPER tabs_nav %]
                    [% WRAPPER tab_item tabname="found" bt_active=1 %] <span>Documents found</span> [% END %]
                    [% WRAPPER tab_item tabname="notfound" %] <span>Documents not found</span> [% END %]
                [% END # /WRAPPER tabs_nav %]

                [% WRAPPER tab_panels %]
                    [% WRAPPER tab_panel tabname="found" bt_active=1 %]
                        [% IF ( foundloop ) %]
                            <table id="found">
                                <thead>
                                    <tr>
                                        <th>Match</th>
                                        <th>Title</th>
                                        <th>Title searched</th>
                                        <th>Author</th>
                                        <th>Publisher</th>
                                        <th>Date</th>
                                        <th>ISBN</th>
                                        <th>[% alterlabel | html %]</th>
                                        <th>ISSN</th>
                                        <th>Bnumber</th>
                                        <th>Notes</th>
                                        <th class="noExport NoSort">Actions</th>
                                    </tr>
                                </thead>
                                <tbody>
                                    [% FOREACH found IN foundloop %]
                                        [% IF ( found.match == 'title' ) %]<tr class="match">[% ELSE %]<tr>[% END %]
                                            <td>[% found.match | html %]</td>
                                            <td>[% found.title | html %]: [% found.subtitle | html %]</td>
                                            <td class="searchedtitle">[% found.searchedtitle | html %]</td>
                                            <td>[% found.author | html %]</td>
                                            <td>[% found.publishercode | html %]</td>
                                            <td>[% found.publicationyear | html %]</td>
                                            <td>[% found.isbn | html %]</td>
                                            <td>[% found.alterid | html %]</td>
                                            <td>[% found.issn | html %]</td>
                                            <td class="biblionumber"><a href="/cgi-bin/koha/catalogue/detail.pl?biblionumber=[% found.biblionumber | html %]">[% found.biblionumber | html %]</a></td>
                                            <td class="editable"><i class="fa fa-edit" aria-hidden="true"></i></td>
                                            <td class="actions">
                                                <div class="btn-group">
                                                    <button class="btn btn-default btn-xs dropdown-toggle" data-toggle="dropdown"><i class="fa fa-wrench"></i> Actions <span class="caret"></span></button>
                                                    <ul class="dropdown-menu">
                                                        <li><a class="delete" href="#"><i class="fa fa-trash" aria-hidden="true"></i> Delete</a></li>
                                                        <li><a class="switch" href="#"><i class="fa fa-share" aria-hidden="true"></i> Switch to Not found</a></li>
                                                    <ul>
                                                </div>
                                            </td
                                        </tr>
                                    [% END # /FOREACH foundloop %]
                                </tbody>
                            </table> <!-- /#found -->
                        [% ELSE %]
                            <span class="term">No documents found</span>
                        [% END # /IF foundloop %]
                    [% END # /WRAPPER tab_panel#found %]

                    [% WRAPPER tab_panel tabname="notfound" %]
                        [% IF ( notfoundloop ) %]
                            <table id="notfound">
                                <thead>
                                    <tr>
                                        <th>Title</th>
                                        <th>Author</th>
                                        <th>Publisher</th>
                                        <th>Date</th>
                                        <th>ISBN</th>
                                        <th>[% alterlabel | html %]</th>
                                        <th>ISSN</th>
                                        <th>Notes</th>
                                    </tr>
                                </thead>
                                <tbody>
                                    [% FOREACH notfound IN notfoundloop %]
                                        <tr>
                                            <td>[% notfound.title | html %]</td>
                                            <td>[% notfound.author | html %]</td>
                                            <td>[% notfound.publisher | html %]</td>
                                            <td>[% notfound.pubdate | html %]</td>
                                            <td>[% notfound.isbn | html %]</td>
                                            <td>[% notfound.alterid | html %]</td>
                                            <td>[% notfound.issn | html %]</td>
                                            <td class="editable"><i class="fa fa-edit" aria-hidden="true"></i></td>
                                        </tr>
                                    [% END # /FOREACH loop %]
                                </tbody>
                            </table> <!-- /#notfound -->
                        [% ELSE %]
                            <span class="term">No documents not found</span>
                        [% END # /IF notfound %]
                    [% END # /WRAPPER tab_panel#notfound %]
                [% END # /WRAPPER tab_panels %]
            [% END # /WRAPPER tabs %]

        </div>
        <div class="col-sm-2 col-sm-pull-10">
            [% INCLUDE 'tools-menu.inc' %]
        </div>
    </div> <!-- row -->
