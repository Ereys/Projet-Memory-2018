Voici le projet 2018 : Memory of Legends.

---------=== Pour installer la bibliothéque graphique===--------------------------------------------------------------------------

    Lancer le script configure pour préparer la compilation et l'installation : : ./configure --prefix=/usr --disable-exemples

--prefix permet de choisir le repertoire d'installation. --enable/--disable-exemples permet de construire ou non la librairie avec des exemples. (ExempleMandelbrot,ExempleSouris, ExempleGraphique, ExempleSprite). --enable/--disable-xpm permet ou non le support des images de format xpm. Faire configure --help pour avoir la liste de toutes les options.

/!\ IMPORTANT : La librairie dépend de la librairie X11 qui doit être installée préalablement et optionnellement de la librairie XPM. /!\

    Lancez la commande make pour la compilation et make install pour l'installation.

    Lancez make uninstall pour la désinstallation.

---------=== Pour lancer le jeu===--------------------------------------------------------------------------

    make: pour compiler
    make clean: pour nettoyer.
    make run: pour compiler et exécuter
