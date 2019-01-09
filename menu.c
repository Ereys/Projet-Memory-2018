


 
    /*Creator : Trivial Corp.*/

    #include <stdio.h>
    #include <stdlib.h>
    #include <graph.h>
    #include <string.h>
    #include <unistd.h>
    #define LFENETRE 1280 
    #define HFENETRE 720



    int Accueil(int Largeur, int Hauteur, int choix);
    int EcranChoix(int Largeur, int Hauteur, int choix);
    void Intro();


    int Accueil(int Largeur, int Hauteur, int choix)  {

        int test = 0;
        choix = 0;
        int posx, posy;
        ChoisirEcran(0);
        ChoisirTitreFenetre("Accueil - Memory Of LegendS");
        ChargerImageFond("Img/accueil.jpg");                        
        ChargerImage("Img/MoLRedi.png",360,10,0,0,775,294);   
        ChargerImage("Img/jouerRedi.png",420,550,0,0,500,50);
        ChargerImage("Img/QuitterRedi.png",420,650,0,0,500,50);
        while (1){
            SourisPosition();                         /* Coordonnée de la souris dans les variables _X et _Y */
            posx =_X;                          
            posy =_Y;
            if(SourisCliquee()) {
                if((posx >= 420)&&(posx <= 920)) {              /* Quitter le jeu */
                    if((posy >= 650)&&(posy <= 700)) {
                        FermerGraphique();
                        exit(0);
                    }
                }
                if((posx >= 420)&&(posx <= 920)) {          /* Affichage de la selection niveau */
                    if((posy >= 550)&&(posy <= 600)) {
                        choix = EcranChoix(LFENETRE,HFENETRE,choix);
                        return choix;
                    }
                }
            }
        }
    }

    /* Ecran de Choix --------------------------------------------- */

    int EcranChoix(int Largeur, int Hauteur, int choix){

        int posx,posy;
        ChoisirTitreFenetre("Selection du niveau - Memory Of LegendS");                      /* Affiche le menu de choix */
        ChargerImageFond("Img/choix.jpg");
        ChargerImage("Img/Easy.jpg",230,400,0,0,128,128);
        ChargerImage("Img/Medium.jpg",580,400,0,0,128,128);
        ChargerImage("Img/Hard.jpg",930,400,0,0,128,128);
        ChargerImage("Img/Back.png", 75, 620,0,0,75,75);

        while(1) {
            if(SourisCliquee()) {
                SourisPosition();     
                posx =_X;           
                posy =_Y;
                if((posx >= 75)&&(posx <= 150)) {          /* Affichage de l'aide */
                    if((posy >= 620)&&(posy <= 695)) {
                        Accueil(LFENETRE,HFENETRE,0);
                    }
                }
                if((posx >= 230)&&(posx <= 358)) {          /* Affichage de l'aide */
                    if((posy >= 400)&&(posy <= 475)) {
                        return choix = 1;
                    }
                }
                if((posx >= 580)&&(posx <= 708)) {          /* Affichage de l'aide */
                    if((posy >= 400)&&(posy <= 475)) {
                        return choix = 2;
                    }
                }   
                if((posx >= 930)&&(posx <= 1058)) {          /* Affichage de l'aide */
                    if((posy >= 400)&&(posy <= 475)) {
                       return choix = 3;
                    }
                }                         
            }
        }
    }
 
    void Intro(){                                 /* Intro du jeu */
        char nom[25];
        int i;
        ChoisirCouleurDessin(CouleurParNom("white"));
        for (i = 1; i < 414; i++){
            sprintf(nom,"./intro/test-%.4d.jpg",i);
            ChargerImage(nom,0,0,0,0,LFENETRE,HFENETRE);
            EcrireTexte(20,700,"Space to skip", 1);
            if (ToucheEnAttente()){
                if (Touche()==XK_space){
                    break;
                }
            }
            usleep(5000);
        }

    }
