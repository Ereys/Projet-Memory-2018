#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include <time.h>
#include <unistd.h>

#include "menu.h"
#include "jeu.h"

#define LFENETRE 1280
#define HFENETRE 720
#define TABMAX 15

int main(int argc, char * argv[]){

  	int x,y,a,b,Margex=0,Margey=0;
    int Taille1,Taille2;
  	int map[TABMAX][TABMAX] = {0};
  	int line,step,col;
  	int choix =  0;
    int paires = 0, fin = 0;

  	InitialiserGraphique();
  	CreerFenetre(200,0,1280,720);                  /*Regroupe les fonctions graphiques au lancement d'une partie */
  	ChoisirTitreFenetre("Memory Of LegendS");
    Intro();


  	choix = Accueil(LFENETRE,HFENETRE,choix);

 	
 	if(choix == 1) {                    /* DIfférents niveaux de difficulté | valeur renvoyée par la fonction EcranChoix(); */
    Taille1 = 4;
    Taille2 = 4;
    Margex =425;
    Margey =100;
  }
    if(choix == 2) {
    Taille1 = 6;
    Taille2 = 6;
    Margex =350;
    Margey =0;
  }
      
    if(choix == 3) {
    Taille1 = 12;
    Taille2 = 7;
    Margex =0;
    Margey =0;
  }
    int seconde = 0;
    int tot= Taille1*Taille2;
    int nbcartes = tot/2;

    ChargerImageFond("Img/temp.jpg");
  	srand(time(NULL));

    ChoisirEcran(4);
    ChargerImageFond("Img/temp.jpg");

    ChoisirEcran(0);
  	Initialiser0(Taille1,Taille2,map);         									/*Cette partie est dediee a la preparation de la surface de jeu*/
 		RemplissageMap(nbcartes,Taille1,Taille2,map);
 		AfficherCartes(Taille1,Taille2, Margex, Margey);


   while(fin == 0) {
      Timer(&seconde);
		  fin = FlipCard(Taille1, Taille2, nbcartes, map,Margex, Margey, &paires);
      }

    EffacerEcran((CouleurParNom("white")));
    ChargerImage("Img/2ni.png",250,0,0,0,720,960);											/*Denis symbolise la victoire*/															
    EcrireTexte(300,100,"Denis vous felicite, c'est une victoire !",2);   
    sleep(3);
    FermerGraphique();

    return EXIT_SUCCESS;
}