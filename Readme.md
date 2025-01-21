## Koha plugin Search from list

Ce programme permet de lancer une recherche de documents à partir d'une liste téléchargée dans un format normalisé (xlsx, odt, csv).  
Les ouvrages trouvés et non trouvés sont affichés chacuns dans deux onglets séparés.  
Il fonctionne avec les moteurs de recherche ElasticSearch ou Zebra.  
La recherche se fait par identifiant (isbn, issn et autres) ou par titre (en combinaison si nécessaire avec l'auteur, l'éditeur et la date d'édition), selon le choix fait dans la page de lancement.  
Un mapping par défaut est établi entre les types de clé proposés par le plugin et les champs de recherche du moteur utilisé.  
Vous pouvez choisir d'autres champs correspondants (ou alias) parmi ceux qui sont définis dans votre configuration ElasticSearch ou dans le fichier _ccl.properties_ pour Zebra. 

### Prérequis

* Koha version 22.11 et suivantes.

* Les utilisateurs doivent avoir la permission d'utiliser les plugins Outils.

### Installation

1. Téléchargez le fichier kpz (Koha Plugin Zip) à partir de la [page des releases](https://github.com/oliviercrouzet/koha-plugin-searchfromlist/releases).  

2. Dans le fichier de configuration de Koha (koha-conf.xml) :

- vérifiez  que l'utilisation des plugins est activée  

    `<enable_plugins>1</enable_plugins>`

- assurez-vous que le chemin du répertoire de plugin est défini  
  
    `<plugindir>my_plugin_dir_path</plugindir>`  

3. Transférez le fichier kpz ou zip dans ce répertoire et décompressez     

    `unzip koha-plugin-searchfromlist-[version].kpz`

4. Initialisez la prise en charge du plugin  

    `perl [KOHADIR]/misc/devel/install_plugins.pl`  

5. Relancez le service Plack  

- Quelque chose comme :

    `koha-plack --restart` (si vous disposez des commandes Debian)

- ou peut-être :

    `sudo systemctl restart koha-plack.target`

--------------------------

## Koha plugin Search from list

This program allows you to search for documents from a list downloaded in a standardized format (xlsx, odt, csv).  
Documents found and not found are displayed both in separate tabs.  
It works with ElasticSearch or Zebra search engines.  
Searches are made by identifier (isbn, issn and others) or by title (if necessary in combination with author, publisher and date of publication), depending on the choice made on the launch page.  
A default mapping is established between the key types proposed by the plugin and the search fields of the engine used.  
You can choose other matching fields (or aliases) from those defined in your ElasticSearch configuration or in the _ccl.properties_ file for Zebra.  

### Requirements

* Koha version 22.11 and later

* Users must have permissions on Tools plugins.                                                          

### Installation

1. Download the kpz (Koha Plugin Zip) file from the [releases page](https://github.com/oliviercrouzet/koha-plugin-searchfromlist/releases).  

2. In Koha configuration file (koha-conf.xml):

- Check that plugins are enabled   

    `<enable_plugins>1</enable_plugins>`

- Make sure that the path to the plugin directory is set  

    `<plugindir>my_plugin_dir_path</plugindir>`

3. Transfer the kpz or zip file to this directory and unzip it  

    `unzip koha-plugin-searchfromlist-[version].kpz`

4. Initialize plugin support  

    `perl [KOHADIR]/misc/devel/install_plugins.pl`

5. Restart Plack service

- Something like:

    `koha-plack --restart` (if you have Debian commands)

- or maybe:

    `sudo systemctl restart koha-plack.target`

