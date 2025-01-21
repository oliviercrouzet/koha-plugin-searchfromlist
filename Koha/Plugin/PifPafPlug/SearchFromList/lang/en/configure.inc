<div id="breadcrumbs"><a href="/cgi-bin/koha/mainpage.pl">Home</a> &rsaquo; <a href="/cgi-bin/koha/plugins/plugins-home.pl">Plugins</a> &rsaquo; Search from list : configuration</div>

<div class="main container-fluid">
    <div class="row">
        <div class="col-sm-10 col-sm-push-2">
            <h2>Search for documents from a downloaded list</h2>
            <fieldset id="config" class="rows">
                <legend>Configuration</legend>
                <p>This plugin can work with ElasticSearch or Zebra search engines.<br/>Search by identifier (isbn, issn or other) or by title (in combination with author, publisher and publication date), depending on the choice you make in the <i><a href="#" id="tool">Launch Tool interface.</a></i><br/>
                A default mapping is established between the key types proposed by the plugin and the search fields of the engine used.<br/>You can modify this by choosing other corresponding search field (or alias) from among those defined in your <a href="/cgi-bin/koha/admin/searchengine/elasticsearch/mappings.pl">ElasticSearch configuration</a> or in the <i>ccl.properties</i> file for Zebra.</p>

            <form method="get">
                <input type="hidden" name="class" value="[% CLASS %]"/>
                <input type="hidden" name="method" value="[% METHOD %]"/>
                 <ul>
                    <li>
                        <table>
                            <thead><tr><th>Search key</th><th>Search engine field</th></tr></thead>
                            <tr>
                              <td><label>ISBN</label></td>
                              <td><input name="isbn" value="[% isbn | html %]" type="text"  required="required" /></td>
                            </tr>
                            <tr>
                              <td><label>ISSN</label></td>
                              <td><input name="issn" value="[% issn | html %]" type="text"  required="required" /></td>
                            </tr>
                            <tr>
                              <td><input name="alterlabel" value="[% alterlabel | html %]" type="text" required="required"/></td>
                              <td><input name="alterid" value="[% alterid | html %]" type="text"  required="required" /></td>
                            </tr>
                            <tr>
                              <td><label>Title</label></td>
                              <td><input name="title" value="[% title | html %]" type="text"  required="required" /></td>
                            </tr>
                            <tr>
                              <td><label>Author</label></td>
                              <td><input name="author" value="[% author | html %]" type="text"  required="required" /></td>
                            </tr>
                            <tr>
                              <td><label>Publisher</label></td>
                              <td><input name="publisher" value="[% publisher | html %]" type="text"  required="required" /></td>
                            </tr>
                            <tr>
                              <td><label>Date of publication</label></td>
                              <td><input name="pubdate" value="[% pubdate | html %]" type="text"  required="required" /></td>
                            </tr>
                        </table>
                    </li> 
                    <li class="notes"><i class="fa fa-hand-o-right" aria-hidden="true"></i> Note that for this key, you can also modify the label displayed on the plugin's pages.</li>

                    <input type="submit" name="saveconfig" value="Confirm configuration" />
                </ul>
            </form>
        </div>
        <div class="col-sm-2 col-sm-pull-10">
            [% INCLUDE 'tools-menu.inc' %]
        </div>
    </div> <!-- row -->
