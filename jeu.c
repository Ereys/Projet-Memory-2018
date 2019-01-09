/*Creator : Trivial Corp.*/
#include <stdio.h>
#include <stdlib.h>      
#include <time.h>         /* --> Permet d'inclure srand                        */
#include <unistd.h>       /* --> Permet d'inclure la fonction sleep* et usleep */
#include "graph.h"        /* --> Permet d'inclure la bibliothéque graphique    */
#define LFENETRE 1280
#define HFENETRE 720
#define TABMAX 15
#define DEBUTCARTEX 50
#define FINCARTEX 130
#define DEBUTCARTEY 100
#define FINCARTEY 180
#define CARTEPLUSESPACE 85
#define TAILLECARTE 80
#define Cycle 1000000L              /* --> 1 seconde en microsecondes */


int secondes = 0;
unsigned long suivant;            /* Variable globale utilisée puisqu'on a besoin dans plusieurs fonctions*/
char timer[20];



int RemplissageMap(int nbcartes, int longtab, int largtab,int map[TABMAX][TABMAX]);
int Initialiser0(int longtab, int largtab,int map[TABMAX][TABMAX]);                                      /*Signatures des fonctions */
int alea(int min, int max);
void AfficherCartes(int a,int b,int mx, int my);
int FlipCard(int Taille1,int Taille2, int nbpaires, int map[TABMAX][TABMAX],int mx,int my, int *paires);
int Triche(int Taille1,int Taille2, int mx, int my, int map[TABMAX][TABMAX]);
void Cacher(int mx, int my, int firstx, int firsty, int secondx, int secondy);
void Timer();
void ClearClick();

 /* ------------------------------------- */


void Cacher(int mx, int my, int firstx, int firsty, int secondx, int secondy){    /* Fonction qui cache les mauvaises paires */
    int t=Microsecondes();
    int tmp;
    int flag=0;
    while(flag==0){                /* Tant qu'il ne s'est pas passe une seconde, on attend, ensuite, on cache les images*/
      tmp=Microsecondes();
      Timer();
      if (tmp-t>1000000){
        break;
      }
    }
  ClearClick();
  ChargerImage("Img/carte.png",mx+DEBUTCARTEX+(firstx*CARTEPLUSESPACE),my+DEBUTCARTEY+(firsty*CARTEPLUSESPACE),0,0,TAILLECARTE,TAILLECARTE);      /* Génére les faces des cartes sur les images retournées */
  ChargerImage("Img/carte.png",mx+DEBUTCARTEX+(secondx*CARTEPLUSESPACE),my+DEBUTCARTEY+(secondy*CARTEPLUSESPACE),0,0,TAILLECARTE,TAILLECARTE);
}


 /* ------------------------------------- */


int RemplissageMap(int nbcartes, int longtab, int largtab,int map[TABMAX][TABMAX]){         /* Chaque case du tableau prends une valeur aléatoire entre 1 et largtab-1 */

  int step;

  for (step=0;step<=nbcartes;){
    int a=alea(0,largtab-1) , b=alea(0,longtab-1), compteur=0;    
    do{
      if(map[a][b]!=0){
        a=alea(0,largtab-1);
        b=alea(0,longtab-1);                  /*Si les coordonnees pointent sur une case qui a deja une valeur, regenere des coordonnees*/
      }else{
        compteur++;                           /*Sinon, passer au placement de la carte suivante*/
        map[a][b]=step;
      } 
    }while(compteur!=2);                      /* Tant qu'on a pas mit valeur dans le tableau, refait un tour de boucle, sinon sort de la boucle et incrémente step */
    step++; 
  }
  return map[TABMAX][TABMAX];                 /* Retourne le tableau remplit de valeur aléatoire */
}


 /* ------------------------------------- */

int Initialiser0(int longtab, int largtab,int map[TABMAX][TABMAX]) {

	int line,col;
  	for(line=0; line<largtab; line++){         /* Initialisation un tableau à 0*/
    	for(col=0; col<longtab; col++){
      		map[line][col]=0;
    	}
 	}
    return map[TABMAX][TABMAX];                /* Retourne le tableau remplit de valeur =  */
}



   /* ------------------------------------- */

int alea(int min, int max){
  	int x;                                     /*Renvoie un nombre aleatoire entre min et max*/
  	x=(rand()%(max-min+1))+min;
  	return x;   
}

 /* ------------------------------------- */

void AfficherCartes(int a,int b,int mx,int my){                /* Affiche toutes les cartes en début de parties */
    int x,y;
    for(y=0;y<b;y++){
      	for (x=0; x < a; x++){                                                                  
        	ChargerImage("Img/carte.png",mx+DEBUTCARTEX+(x*CARTEPLUSESPACE),my+DEBUTCARTEY+(y*CARTEPLUSESPACE),0,0,TAILLECARTE,TAILLECARTE);
          usleep(50000);         /* --> affiche les cartes une par une */
      	}
    }    
}

 /* ------------------------------------- */

int FlipCard(int Taille1,int Taille2, int nbpaires, int map[TABMAX][TABMAX],int mx,int my, int *paires){       /* Fonction principale qui fait tourner le jeu */

  int x, y;
  int coup = 0;
  int first = -10,second = -10;
  int firstx = -1, firsty = -1, secondx = 0, secondy = 0;
  int fin = 0;

  while(coup != 2){               /* Tant que coup n'est pas égal à 2 le joueur choisit deux cartes */
    Timer(&secondes);
    if (ToucheEnAttente()==1){
      if (Touche() == XK_t){
        Triche(Taille1,Taille2, mx, my ,map);
      }
    }
    if(SourisCliquee()){
      SourisPosition();                              
      for(y=0;y < Taille2;y++){            /* --> Boucle qui teste toutes les coordonnees où une carte se trouve*/
        for (x=0; x < Taille1; x++){       /*                                                                   */                                                      
          if((_X >= mx+DEBUTCARTEX+(x*CARTEPLUSESPACE))&&(_X <= mx+FINCARTEX+(x*CARTEPLUSESPACE))) {        
            if((_Y >= my+DEBUTCARTEY+(y*CARTEPLUSESPACE))&&(_Y <= my+FINCARTEY+(y*CARTEPLUSESPACE))) {
              if(map[y][x] != -1 && ((x != firstx)||(y != firsty))) {
                char revel[10];
                sprintf(revel,"Img/%d.png",map[y][x]);                           /* --> Si le clic est bien dans l'une de ses zone, afficher la carte correspondante*/
                ChargerImage(revel,mx+DEBUTCARTEX+(x*CARTEPLUSESPACE),my+DEBUTCARTEY+(y*CARTEPLUSESPACE),0,0,TAILLECARTE,TAILLECARTE);
				        coup++;
                if(coup==1){
	                first = map[y][x];           /* Stock la valeur du tableau correspondant au choix */
	                firstx = x;                  /* Si le joueur a cliqué sur une carte --> stock les coordonnée de la carte dans firstx et firsty*/
	                firsty = y;
              	}else{
                second = map[y][x];     /* Stock la valeur du tableau correspondant au choix */
                secondx = x;            /* Stock les coordonnée de la carte dans firstx et secondy*/
                secondy =y;              		
              	}
              }	
            }
          }
        }
      }
    }
  }

  if(first == second) {                    /* Si a valeur du tableau stocker dans first = à la deuxiéme valeur, alors : */
    
    map[firsty][firstx] = -1;              /* Change les valeurs du tableaux en -1, une valeur associé à aucune carte */
    map[secondy][secondx] =  -1;
    *paires+= 1;                           /* Incrémente la variable paires par un pointeur */

  }else{
    Cacher( mx, my, firstx, firsty,secondx, secondy);           /* Sinon les deux cartes se retournent */
  }
  if(*paires==nbpaires) {                                       /* Teste si la variable pointé est égale au nombre de paires max, si oui, alors : */
    return fin = 1;                                             /* Fin de la partie */
  }else{
  return fin = 0;                                               /* Nouveau tour de boucle */
  }
} 

 /* ------------------------------------- */


int Triche(int Taille1,int Taille2, int mx, int my ,int map[TABMAX][TABMAX]) {      /* Permet d'activer le mode triche */
  CopierZone(0,2,0,0,LFENETRE,HFENETRE,0,0);
  ChoisirEcran(1);
  ChargerImageFond("Img/temp.jpg");
  sprintf(timer,"Timer : %5d s",secondes);
  EcrireTexte(1100,625,timer,1);                                /* Stop le timer et le laisse afficher */
  EcrireTexte(100,100,"-=/ Cheat Mode Activated \\=-",2);       /* Permet d'afficher que le mode triche est activé en haut à gauche */

  for(int y=0;y < Taille2;y++){
    for (int x=0; x < Taille1; x++){
      char revel[10];
      sprintf(revel,"Img/%d.png",map[y][x]);                    /* Affiche toute les cartes encore non jouées */
      ChargerImage(revel,mx+DEBUTCARTEX+(x*CARTEPLUSESPACE),my+DEBUTCARTEY+(y*CARTEPLUSESPACE),0,0,TAILLECARTE,TAILLECARTE);
      CopierZone(1,0,0,0,LFENETRE,HFENETRE,0,0);
    }
  }    
  while(1){                                                       /* Mode Triche activé tant qu'on ne rappuie pas sur touche T */
    if(Touche() == XK_t){
      CopierZone(2,0,0,0,LFENETRE,HFENETRE,0,0);
      ClearClick();
      ChoisirEcran(0);
      return 1;
    }
  }
}


 /* ------------------------------------- */

void Timer() {                     /* Affiche le temps */

    if( Microsecondes() - suivant > Cycle) {
      secondes+=1;
      suivant = Microsecondes();
      sprintf(timer,"Timer : %5d s",secondes);               /* Rentre dans timer[] : Timer : secondes s" */
      CopierZone(4,0,1075,600,1200,750,1075,600);   /* A changer pour le fond */
      EcrireTexte(1100,625,timer,1);
    }
  }

 /* ------------------------------------- */

void ClearClick(){                   /* Empêche les clicks de souris dans certaines fonctions , vide le tampon click*/
  int r1,r2;
     while(SourisCliquee()){
        r1=_X;
        r2=_Y;
     }
}


