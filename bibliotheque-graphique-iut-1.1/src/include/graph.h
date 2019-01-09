#ifndef _GRAPH_H
#define _GRAPH_H

#include<X11/Xlib.h>
#include<X11/Xutil.h>
#include<X11/keysym.h>

extern int _X;
extern int _Y;

#define NB_PIXMAP 10

typedef unsigned long couleur;
typedef XPoint Point;

int InitialiserGraphique();
/* initialise le mode graphique : renvoie 1 en cas de succes, 0 sinon */

int CreerFenetre(int posx,int posy,int X,int Y);
/* creer la fenetre graphique de largeur X et longueur Y, et la positionne
   sur l'ecran au point (posx,posy). Une seule fenetre autoris�e */

void ChoisirTitreFenetre(char *s);
/* change le titre de la fenetre */

void ChoisirCurseur(unsigned int forme);
/* change le curseur de la fenetre */

void CacherFenetre(void);
/* cache la fenetre */

void AfficherFenetre(void);
/* affiche la fenetre */

void ChoisirEcran(int n);
/* fixe l'ecran ou le dessin est effectue : cette ecran est soit 0 (la fenetre
   visible, ecran par defaut au demarrage), soit le numero de l'�cran  virtuel correspondant */

void ChoisirCouleurDessin(couleur c);
/* fixe la couleur qui sert au dessin */

couleur CouleurParNom(char * nom);
/* fait la traduction d'une couleur a partir de son nom : le fichier rgb.txt
   contient la liste des couleurs accessibles via leur nom */

couleur CouleurParComposante(unsigned char r, unsigned char v,unsigned char b); 
/* renvoie la couleur d�finie par ses trois composantes */

int Maxx();
/* renvoie la largeur de l'ecran : il faut que le mode graphique ait �t� 
   initialise !!! */

int Maxy();
/* renvoie la hauteur de l'ecran : il faut que le mode graphique ait �t� 
   initialise !!! */

void DessinerPixel(int x,int y);
/* allume un pixel avec la couleur de dessin */

void DessinerSegment(int x,int y,int xx,int yy);
/* idem precedent, mais avec la couleur de dessin */

void DessinerSegments(Point * sommets,int nb_sommets);
/* trace pour chaque paire sommet[i],sommet[i+1] le segment correspondant. Si le deux extr�mit�s correspondent, le polygone est ferm� */

void DessinerRectangle(int x,int y,int l,int h);
/* idem, mais utilise la couleur de dessin */

void RemplirRectangle(int x,int y,int l,int h);
/* trace un rectangle plein, rempli avec c */

void DessinerArc(int x,int y,int l,int h,int angle1,int angle2);
/* idem, mais utilise la couleur de dessin */

void RemplirArc(int x,int y,int l,int h,int angle1,int angle2);
/* trace un arc plein avec c */

void RemplirTriangle(int x,int y,int xx,int yy,int xxx,int yyy);
/* trace un triangle plein */

void RemplirPolygone(Point * sommets,int nb_sommet);
/* Trace un polygone plein d�fini par son tableau de sommets. Si les extremit�s ne coincident pas, le polygone est ferm� automatiquement.
*/

int ToucheEnAttente();
/* renvoie 1 si une touche a �t� enfonc�e, 0 sinon */

KeySym Touche();
/* renvoie la premiere touche du tampon : cette fonction est bloquante => 
   utiliser ToucheEnAttente  pour la rendre non bloquante */

void EcrireTexte(int x,int y,char *texte,int taille);
/* ecrit la chaine texte au point (x,y) : taille indique la taille (0<->petit,1<->moyen,2<->grand) */
#ifdef HAVE_XPM
void SauverImage(char * file,int x,int y,int l,int h);
/* sauvegarde d'une partie de la fenetre (x,y,x+l,y+h) au format xpm */
#endif

int ChargerImage(char *file,int x,int y,int xx,int yy,int l,int h);
/* charge une partie (xx,yy,xx+l,yy+h) d'image au format xpm dans 
la fenetre a la position (x,y) */

void ChargerImageFond(char *file);
/* charge une image qui remplit le fond de la fen\^etre, en la r\'ep\'etant si necessaire */

void EffacerEcran(couleur c);
/* efface l'ecran avec la couleur c*/

void ChoisirModeDessin(int m);
/* fixe le mode d'affichage : 0<->ecrasement 1<->xor */

int TailleChaineEcran(char *t,int taile);
/* renvoie, en pixel, la taille horizontale occupee par la chaine � l'�cran :taille est la taille de la police (0,1,2) */

int TailleSupPolice(int taille);
/* renvoie la taiile maximale de la police, en pixel, au dessus de la ligne d'�criture */

int TailleInfPolice(int taille);
/* renvoie la taille maximale de la police, en pixel, en dessous de la ligne d'�criture */

void CopierZone(int src,int dst,int ox,int oy,int L,int H,int dx,int dy);
/* copie une zone de l'�cran vers l'�cran dst. La zone copi�e est le rectangle delimite par le coin superieure hauche (ox,oy) et sa largeur l et hauteur h. Cette zone est copi� au point (dx,dy) de l'ecran dst */ 

void FermerGraphique();
/* fermeture du mode graphique */

unsigned long Microsecondes();
/* renvoie le nombre de microsecondes ecoul�es depuis le
lancement du programme */

void SourisPosition();
/* recupere les coordonnees de la souris dans la fenetre et les place dans _X et _Y*/

int SourisCliquee();
/* indique un clic de souris (1 si oui, 0 sinon), et recupere si c'est le cas la position au moment du clic dans _X et _Y */


/* fonctions a r��crire proprement */

int ChargerSprite(char *file);
/* charge un srpite en m�moire, et renvoie son num�ro 
 * -1 en cas d'echec */
void AfficherSprite(int n,int x,int y);
/* affiche le sprite correspondant � son num�ro */
void LibererSprite(int n);
/* libere les ressources associ�es au sprite
 * n */

#endif
void FlipCard(int Taille1,int Taille2, int nbpaires, int map[TABMAX][TABMAX] ){

  int x, y, posx, posy;
  int coup = 0;
  int first = -10,second = -10;
  int firstx = -1, firsty = -1, secondx = 0, secondy = 0;
  int paires = 0;
  int fin = 0;

  while(coup != 2){                              /* Tant que coup n'est pas �gale � 1 le joueur choisit une carte */
    if(SourisCliquee()){
      SourisPosition();     
      posx =_X;                          
      posy =_Y;
      for(y=0;y < Taille2;y++){
        for (x=0; x < Taille1; x++){
          if((posx >= 50+(x*85))&&(posx <= 130+(x*85))) {        
            if((posy >= 100+(y*85))&&(posy <= 180+(y*85))) {
              if(map[y][x] != -1 && ((x != firstx)||(y != firsty))) {
                char revel[10];
                sprintf(revel,"Img/%d.png",map[y][x]);
                ChargerImage(revel,50+(x*85),100+(y*85),0,0,80,80);
				        coup++;
                if(coup==1){
	                first = map[y][x]; 
	                firstx = x;                  /* Stock les coordonn�e de la carte dans x et y */
	                firsty = y;
              	}else{
                second = map[y][x];     /* Stock la valeur du tableau correspondant au choix */
                secondx = x;            /* Stock les coordonn�e de la carte dans x et y */
                secondy =y;              		
              	}
              }	
            }
          }
        }
      }
    }
  }
  if(first == second) {
    char revel[10];
    sprintf(revel,"Img/%d.png",map[firsty][firstx]);
    ChargerImage(revel,50+(firstx*85),100+(firsty*85),0,0,80,80);
    sprintf(revel,"Img/%d.png",map[firsty][firstx]);
    ChargerImage(revel,50+(secondx*85),100+(secondy*85),0,0,80,80);
    map[firsty][firstx] = -1;
    map[secondy][secondx] =  -1;
    paires++;

  }else{
    sleep(1);
    ChargerImage("Img/carte.png",50+(firstx*85),100+(firsty*85),0,0,80,80);
    ChargerImage("Img/carte.png",50+(secondx*85),100+(secondy*85),0,0,80,80);
  }
} 

