<div id="breadcrumbs"><a href="/cgi-bin/koha/mainpage.pl">Home</a> &rsaquo; <a href="/cgi-bin/koha/plugins/plugins-home.pl">Plugins</a> &rsaquo; Search from list</div>

<div class="main container-fluid">
    <div class="row">
        [% IF ( error ) %]
            <div  class="errorfile"><i class="fa fa-exclamation-triangle" aria-hidden="true"></i> The downloaded file [% IF ( error == 'empty' ) %]is empty[% ELSE %]is not in a valid format[% END %].</div>
        [% END %]
        <div class="col-sm-10 col-sm-push-2">
            <h2> Search for documents from a list</h2>
            <form method="post" id="listsearch" action="/cgi-bin/koha/plugins/run.pl?class=[% CLASS %]&method=[% METHOD %]" enctype="multipart/form-data">
                [% INCLUDE 'csrf-token.inc' %]
                <input type="hidden" name="class" value="[% CLASS %]"/>
                <input type="hidden" name="method" value="[% METHOD %]"/>
                <fieldset>
                    <ol>
                        <li>
                            <input name="uploadfile" type="file" id="uploadfile" required="required"/>
                            <div class="hint">files accepted: Excel and Calc (1st sheet only), csv files, tabulated files.</div>
                        </li>
                    </ol>
                </fieldset>
                <fieldset id="searchkeys" class="rows">
                    <h3>Search keys</h3>
                    <div class="hint">To set which columns contain the search keys in the file to be imported, you can use either column headings, column numbers or letters.<br/>The search is performed successively, in the order of the keys entered. Please note that the Author, Publisher and Publication date keys must be combined with the Title key if they are indicated.</div>
                    <fieldset>
                        <ol>
                        <li>
                            <label for="isbn"> ISBN:</label>
                                <input name="isbn" class="number" type="text" value=""/>
                        </li>
                        <li>
                            <label for="issn"> ISSN:</label>
                                <input name="issn" class="number" type="text" value=""/>
                        </li>
                        <li>
                            <label for="alterid"> [% alterlabel | html %]:</label>
                                <input name="alterid" class="number" type="text" value=""/>
                        </li>
                        <li>
                            <label for="title"> Title:</label>
                                <input name="title" id="title" type="text" value="" required="required"/>
                        </li>
                        <li>
                            <label for="author"> Author:</label>
                                <input name="author" id="author" type="text" value=""/>
                        </li>
                        <li>
                            <label for="publisher"> Publisher:</label>
                                <input name="publisher" id="publisher" type="text" value=""/>
                        </li>
                        <li>
                            <label for="pubdate"> Date of publication:</label>
                                <input name="pubdate" id="pubdate" type="text" value=""/>
                        </li>
                        </ol>
                        <div class="hint">Specify key columns using a single type of reference: headings, numbers or letters. Case is ignored.</div>
                        <input type="submit" class="btn btn-primary" value="Launch search"/>
                    </fieldset>
                </fieldset>
            </form>
        </div>
        <div class="col-sm-2 col-sm-pull-10">
            [% INCLUDE 'tools-menu.inc' %]
        </div>
    </div> <!-- row -->
