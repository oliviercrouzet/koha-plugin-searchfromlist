<div id="breadcrumbs"><a href="/cgi-bin/koha/mainpage.pl">Home</a> &rsaquo; <a href="/cgi-bin/koha/plugins/plugins-home.pl">Plugins</a> &rsaquo; Search from list</div>

<div class="main container-fluid">
    <div class="row">
        [% IF ( error ) %]
            <div  class="errorfile"><i class="fa fa-exclamation-triangle" aria-hidden="true"></i> Le fichier téléchargé [% IF ( error == 'empty' ) %]est vide [% ELSE %]n'est pas dans un format valide[% END %].</div>
        [% END %]
        <div class="col-sm-10 col-sm-push-2">
            <h2> Recherche de documents à partir d'une liste</h2>
            <form method="post" id="listsearch" action="/cgi-bin/koha/plugins/run.pl?class=[% CLASS %]&method=[% METHOD %]" enctype="multipart/form-data">
                [% INCLUDE 'csrf-token.inc' %]
                <input type="hidden" name="class" value="[% CLASS %]"/>
                <input type="hidden" name="method" value="[% METHOD %]"/>
                <fieldset>
                    <ol>
                        <li>
                            <input name="uploadfile" type="file" id="uploadfile" required="required"/>
                            <div class="hint">fichiers acceptés : Excel et Calc (1ère feuille prise en compte uniquement), fichiers csv, fichiers tabulés.</div>
                        </li>
                    </ol>
                </fieldset>
                <fieldset id="searchkeys" class="rows">
                    <h3>Clés de recherche</h3>
                    <div class="hint">Pour désigner quelles colonnes contiennent les clés de recherche dans le fichier à importer, vous pouvez utiliser soit les intitulés de colonnes, soit les numéros de colonnes, soit les lettres.<br/>La recherche est faite successivement, dans l'ordre des clés renseignées. Notez que les clés Auteur, Editeur et Date de publi. sont obligatoirement combinées avec la clé Titre si elles sont indiquées.</div>
                    <fieldset>
                        <ol>
                        <li>
                            <label for="isbn"> ISBN :</label>
                                <input name="isbn" class="number" type="text" value=""/>
                            <label for="issn"> ISSN :</label>
                                <input name="issn" class="number" type="text" value=""/>
                            <label for="alterid"> [% alterlabel | html %] :</label>
                                <input name="alterid" class="number" type="text" value=""/>
                            <label for="title"> Titre :</label>
                                <input name="title" id="title" type="text" value=""/>
                            <label for="author"> Auteur :</label>
                                <input name="author" id="author" type="text" value=""/>
                            <label for="publisher"> Éditeur :</label>
                                <input name="publisher" id="publisher" type="text" value=""/>
                            <label for="pubdate"> Date de publ. :</label>
                                <input name="pubdate" id="pubdate" type="text" value=""/>
                        </li>
                        <li>
                            <div class="hint">Indiquez les colonnes clés en utilisant un seul type de référence : intitulés, numéros ou lettres. La casse est ignorée.</div>
                        </li>
                        </ol>
                        <input type="submit" class="btn btn-primary" value="Importer"/>
                    </fieldset>
                </fieldset>
            </form>
        </div>
        <div class="col-sm-2 col-sm-pull-10">
            [% INCLUDE 'tools-menu.inc' %]
        </div>
    </div> <!-- row -->
