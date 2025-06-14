<div id="breadcrumbs"><a href="/cgi-bin/koha/mainpage.pl">Home</a> &rsaquo; <a href="/cgi-bin/koha/plugins/plugins-home.pl">Plugins</a> &rsaquo; Search from list &rsaquo; Configuration</div>

<div class="main container-fluid">
    <div class="row">
        <div class="col-sm-10 col-sm-push-2">
            <h2>Recherche automatique de documents à partir d'une liste téléchargée</h2>
            <fieldset id="config" class="rows">
                <legend>Configuration</legend>
                <p>Ce plugin peut fonctionner avec les moteurs de recherche ElasticSearch ou Zebra.<br/>La recherche se fait par identifiant (isbn, issn et autre) ou par titre (en combinaison avec l'auteur, l'éditeur et la date d'édition), selon le choix que vous faîtes dans l'interface <i><a href="#" id="tool">Lancer l'outil</a>.</i><br/>
                Un mapping par défaut est établi entre les types de clé proposés par le plugin et les champs de recherche du moteur utilisé.<br/>Vous pouvez choisir d'autres champs correspondants (ou alias) parmi ceux qui sont définis dans votre <a href="/cgi-bin/koha/admin/searchengine/elasticsearch/mappings.pl">configuration ElasticSearch</a> ou dans les fichiers <i>ccl.properties et biblio-koha-indexdefs.xml</i> pour Zebra.</p>

            <form method="get">
                <input type="hidden" name="class" value="[% CLASS %]"/>
                <input type="hidden" name="method" value="[% METHOD %]"/>
                 <ul>
                    <li>
                        <table>
                            <thead><tr><th>Clé de recherche</th><th>Champ du moteur de recherche</th></tr></thead>
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
                              <td><label>Titre</label></td>
                              <td><input name="title" value="[% title | html %]" type="text"  required="required" /></td>
                            </tr>
                            <tr>
                              <td><label>Auteur</label></td>
                              <td><input name="author" value="[% author | html %]" type="text"  required="required" /></td>
                            </tr>
                            <tr>
                              <td><label>Éditeur</label></td>
                              <td><input name="publisher" value="[% publisher | html %]" type="text"  required="required" /></td>
                            </tr>
                            <tr>
                              <td><label>Date de publication</label></td>
                              <td><input name="pubdate" value="[% pubdate | html %]" type="text"  required="required" /></td>
                            </tr>
                        </table>
                    </li> 
                    <li class="notes"><i class="fa fa-hand-o-right" aria-hidden="true"></i> Notez que vous pouvez aussi, pour cette clé, modifier le label qui est affiché dans les pages du plugin.</li>

                    <input type="submit" name="saveconfig" value="Validez la configuration" />
                </ul>
            </form>
        </div>
        <div class="col-sm-2 col-sm-pull-10">
            [% INCLUDE 'tools-menu.inc' %]
        </div>
    </div> <!-- row -->
