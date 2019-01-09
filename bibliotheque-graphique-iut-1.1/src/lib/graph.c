#include<X11/Xlib.h>
#include<X11/cursorfont.h>
#include<X11/Xatom.h>
#include<X11/Xutil.h>
#include<X11/keysym.h>

#include<stdio.h> 
#include<stdlib.h>
#include<string.h>
#include<time.h>

#include "config.h"

#ifdef HAVE_XPM
#include<X11/xpm.h>
#endif


#include "graph.h"
#include "image.h"
#define N 50


void _get_GC(Window win, GC *gc);

typedef struct
{
	int posx,posy;
	int tx,ty;
	int etat;
	Pixmap s;
	Pixmap smask;
	Pixmap sauvegarde;
}
sprite;

sprite S[N];                        /* tableau de sprite    */
int S_alloue[N];					/* tableau d'allocation */

/******************** variables globales  beurk ****************************/

Display *display;
int screen;
int display_width=0,display_height=0;
int X_fen,Y_fen;
int connecte=0;
int nbfen=0;
Window win;
XColor coul;
unsigned long couleur_dess;
XEvent report;		                 /* structure des evenements */

GC gc;					             /* ID du contexte graphique */
unsigned int border_w=4; 
Cursor croix;
XSetWindowAttributes attribut;
Colormap pal;					     /* palette 			*/
Font f[3];							 /* polices d'ecriture          */
XFontStruct *s[3];
XFontStruct *stemp;
Pixmap icone=NULL,icone_mask=NULL;
XPoint sommet[3];
int num_ecran=0;
Window ecran[NB_PIXMAP+1];
int app=0;
XWMHints  * wm_hints;
XClassHint  * class_hints;
XSizeHints  * size_hints;

XTextProperty nom_fenetre,nom_icone;
char *nf="IUT de Fontainebleau"; // changer si vous voulez :-)
char *ni="mon_icone";          

int _X=0,_Y=0;

//#include "image.c"

void  ChoisirModeDessin(int m)
{
	switch(m)
	{
		case 0 : XSetFunction(display,gc,GXcopy);
				 break;
		case 1 : XSetFunction(display,gc,GXxor);
				 break;
		case 2 : XSetFunction(display,gc,GXinvert);
				 break;
		default : XSetFunction(display,gc,GXcopy); 
	}  
}
void ChoisirCouleurDessin(unsigned long couleur)
{
	couleur_dess=couleur;
	XSetForeground(display,gc,couleur);
	XFlush(display);
}

void ChoisirEcran(int n)
{
	if (0<=n&&n<=NB_PIXMAP) num_ecran=n;
}

int InitialiserGraphique()
{
	if (!connecte)
	{
		if((display=XOpenDisplay(NULL))==NULL) {
			fprintf(stderr,"erreur : ne peut pas se connecter ");
			fprintf(stderr,"au serveur %s\n",XDisplayName(NULL));
			return 0;
		}
		if (connecte) //return 0;
		return 1;	

		/* Recuperer les informations concernant l'ecran (root window) sur
		   lequel on va afficher notre application. Le numero de l'ecran
		   par defaut s'obtient a l'aide de la macro DefaultScreen(), la
		   taille a l'aide des macros DisplayWidth() et
		   DisplayHeight().*/

		screen = DefaultScreen(display);
		display_width = DisplayWidth(display,screen);
		display_height = DisplayHeight(display,screen);
		pal=DefaultColormap(display,screen);
		connecte=1;
		return 1;
	}
}

int CreerFenetre(int posx,int posy,int X,int Y)
{
	int i;
	Visual *v;
	char buf[1024]; 
	int trouve;

	if (!connecte) 
	{
		perror("initialisez d'abord le mode graphique\n");
		//return (1);
		return 0;
	}

	if (nbfen==1) 
	{
		printf("une seule fentre on a dit !!!!\n");
		//return(1);
		return 0;
	}

	ecran[0] = XCreateSimpleWindow(display, RootWindow(display, screen), 
			posx, posy,X, Y, border_w,
			BlackPixel(display,screen),
			WhitePixel(display,screen));

	/* sensibilisation de la fenêtre */

	XSelectInput(display, ecran[0], 
			ExposureMask | KeyPressMask |ButtonPressMask  );


	/* creation d'un contexte graphique pour cette fenetre,
	   indispensable pour dessiner ou afficher du texte */

	_get_GC(ecran[0], &gc);

	/* creation d'une fonte curseur */

	croix=XCreateFontCursor(display,XC_crosshair);
	XDefineCursor(display,ecran[0],croix);

	/* le contenu de la fenetre est persistant : le serveur le supporte-t-il ? */       

	attribut.backing_store=Always;
	XChangeWindowAttributes(display,ecran[0],CWBackingStore,&attribut);

	/* chargement d'une font par defaut pour l'ecriture de texte */

	trouve=0;
	i=10;
	while(!trouve&&i<=15)
	{
		sprintf(buf,"-adobe-helvetica-*-r-*-*-%d-*-*-*-*-*-*-*",i);
		stemp=XLoadQueryFont(display,buf);
		if (stemp==NULL) i++;
		else
			trouve=1;
	}

	if (!trouve) 
	{
		sprintf(buf,"6x13");
		if ((stemp=XLoadQueryFont(display,buf))==NULL)
			stemp=XLoadQueryFont(display,"fixed");
	}
	f[0]=stemp->fid;
	s[0]=stemp;


	trouve=0;
	i=20;
	while(!trouve&&i<=25)
	{
		sprintf(buf,"-adobe-helvetica-*-r-*-*-%d-*-*-*-*-*-*-*",i);
		stemp=XLoadQueryFont(display,buf);
		if (stemp==NULL) i++;
		else
			trouve=1;
	}
	if (!trouve) 
	{
		sprintf(buf,"8x16");
		if ((stemp=XLoadQueryFont(display,buf))==NULL)
			stemp=XLoadQueryFont(display,"fixed");
	}
	f[1]=stemp->fid;
	s[1]=stemp;


	trouve=0;
	i=30;
	while(!trouve&&i<=35)
	{
		sprintf(buf,"-adobe-helvetica-*-r-*-*-%d-*-*-*-*-*-*-*",i);
		stemp=XLoadQueryFont(display,buf);
		if (stemp==NULL) i++;
		else
			trouve=1;
	}
	if (!trouve) 
	{
		sprintf(buf,"12x24");
		if ((stemp=XLoadQueryFont(display,buf))==NULL)
			stemp=XLoadQueryFont(display,"fixed");
	}

	f[2]=stemp->fid;
	s[2]=stemp;


	XSetFont(display,gc,f[1]);



	/* creation des pixmaps pour la sauvegarde d'images */

	for(i=1;i<=NB_PIXMAP;i++)
	{ 
		ecran[i]=XCreatePixmap( display , DefaultRootWindow(display), X , Y , DefaultDepth(display,screen) );
	} 
	/* variables globales pour la taille de la fenetre */

	X_fen=X;
	Y_fen=Y;

	bzero(S_alloue,N*sizeof(int));
	wm_hints=XAllocWMHints();
	class_hints=XAllocClassHint();
	size_hints=XAllocSizeHints();

	XStringListToTextProperty(&nf,1,&nom_fenetre);
	XStringListToTextProperty(&ni,1,&nom_icone);
	wm_hints->initial_state=NormalState;
	wm_hints->input=True;
	wm_hints->flags=StateHint|InputHint;
	size_hints->x=posx;
	size_hints->y=posy;
	size_hints->flags=USPosition;
	//class_hints->res_name="Graphique";
	XSetWMProperties(display,ecran[0],&nom_fenetre,&nom_icone,NULL,0,size_hints,wm_hints,NULL);
	//XSetWMNormalHints(display,ecran[0],size_hints);
	XSetIconName(display,ecran[0],"Super");
	//  XStoreName(display,ecran[0],"D.M Entertainment");
	XMapWindow(display,ecran[0]);

	XFree(wm_hints);
	XFree(size_hints);
	XFree(class_hints);
	wm_hints=XGetWMHints(display,ecran[0]);
	do 
	{
		XWindowEvent(display,ecran[0],ExposureMask,&report);
	}
	while(report.xexpose.count);
	nbfen=1;
	return 1;
}

void ChoisirTitreFenetre(char *s)
{
	XStoreName(display,ecran[0],s );
}
void ChoisirCurseur(unsigned int forme)
{
	XFreeCursor(display,croix);
	croix=XCreateFontCursor(display,forme);
	XDefineCursor(display,ecran[0],croix);
}


/*----------------------*/

void _get_GC(Window win, GC *gc)

{
	unsigned long valuemask = 0;                /* Ignore XGCvalues et prend les
												   valeurs par defaut */
	XGCValues values;

	/* creation d'un contexte graphique par defaut */

	*gc = XCreateGC(display, ecran[0], valuemask, &values);


	/* specification d'un background noir, puisque par defaut on fait du
	   blanc sur du blanc */
	//XSetBackground(display,*gc,154);

	XSetForeground(display, *gc, BlackPixel(display, screen));
	XSetGraphicsExposures(display,*gc,False);	 

	/* inutile d'enfler la file d'evenements avec les evenements
	   Noexpose et GraphicsExpose */
}

int Maxx()
{
	if (!connecte) return -1;
	else return display_width;
}

int Maxy()
{
	if (!connecte) return -1;
	else return display_height;
}

void DessinerPixelC(int x,int y,unsigned long couleur)
{
	XSetForeground(display,gc,couleur);
	XDrawPoint(display,ecran[num_ecran],gc,x,y);
	XSetForeground(display,gc,couleur_dess);
	XFlush(display);
}

void DessinerPixel(int x,int y)
{
	XDrawPoint(display,ecran[num_ecran],gc,x,y);
	XFlush(display);
}

void DessinerSegmentC(int x,int y,int xx,int yy,unsigned long couleur)
{
	XSetForeground(display,gc,couleur);
	XDrawLine(display,ecran[num_ecran],gc,x,y,xx,yy);
	XSetForeground(display,gc,couleur_dess);
	XFlush(display);
}
void DessinerSegment(int x,int y,int xx,int yy)
{
	XDrawLine(display,ecran[num_ecran],gc,x,y,xx,yy);
	XFlush(display);
}

void FermerGraphique()
{ 
	int i;
	XSync(display,True);
	for (i=0;i<3;i++) XUnloadFont(display,f[i]);
	for (i=1;i<=NB_PIXMAP;i++)
		XFreePixmap(display,ecran[i]);
	for(i=0;i<N;i++) LibererSprite(i);
	XFreeGC(display,gc);
	XCloseDisplay(display);
	nbfen=0;
	connecte=0;
	app=0;
}

unsigned long CouleurParNom(char * nom)
{
	XParseColor(display,pal,nom,&coul);
	XAllocColor(display,pal,&coul);
	return coul.pixel;
}

void DessinerRectangleC(int x,int y,int l,int h,unsigned long c)
{
	XSetForeground(display,gc,c);
	XDrawRectangle(display,ecran[num_ecran],gc,x,y,l,h);
	XSetForeground(display,gc,couleur_dess);
	XFlush(display);
}
void DessinerRectangle(int x,int y,int l,int h)
{

	XDrawRectangle(display,ecran[num_ecran],gc,x,y,l,h);
	XFlush(display);

}
void RemplirRectangle(int x,int y,int l,int h)
{
	XFillRectangle(display,ecran[num_ecran],gc,x,y,l,h);
	XFlush(display);
}

void DessinerArcC(int x,int y,int l,int h,int angle1,int angle2,unsigned long c)
{
	XSetForeground(display,gc,c);
	XDrawArc(display,ecran[num_ecran],gc,x,y,l,h,angle1*64,angle2*64);
	XSetForeground(display,gc,couleur_dess);
	XFlush(display);
}

void DessinerArc(int x,int y,int l,int h,int angle1,int angle2)
{
	XDrawArc(display,ecran[num_ecran],gc,x,y,l,h,angle1*64,angle2*64);
	XFlush(display);

}

void RemplirArc(int x,int y,int l,int h,int angle1,int angle2)
{
	XFillArc(display,ecran[num_ecran],gc,x,y,l,h,angle1*64,angle2*64);
	XFlush(display);
}


void DessinerSegments(Point * sommets,int nb_sommet)
{
	XDrawLines(display,ecran[num_ecran],gc,
			sommets,nb_sommet, CoordModeOrigin);
}

void RemplirPolygone(Point * sommets,int nb_sommet)
{
	XFillPolygon(display, ecran[num_ecran],gc, sommets,
			nb_sommet, Complex,CoordModeOrigin);
}
void RemplirTriangle(int x,int y,int xx,int yy,int xxx,int yyy)
{
	sommet[0].x=(short)x;
	sommet[0].y=(short)y;
	sommet[1].x=(short)xx;
	sommet[1].y=(short)yy;
	sommet[2].x=(short)xxx;
	sommet[2].y=(short)yyy;
	XFillPolygon(display,ecran[num_ecran],gc,sommet,3,Convex,CoordModeOrigin);
	XFlush(display);
}

int ToucheEnAttente()
{
	if (app==1) return 1;
	if (XCheckWindowEvent(display,ecran[0],KeyPressMask,&report)) 
	{
		app=1;
		return 1;
	}
	//app=0;
	return 0;
}


KeySym Touche()
{
	/* fonction bloquante si aucune touche dans le buffer
	*/
	int  buffer;
	int c;
	KeySym t;
	if (app==0)	XWindowEvent(display,ecran[0],KeyPressMask,&report);
	c=XLookupString(&(report.xkey), NULL, sizeof(KeySym), &t,NULL);
	app=0;
	return t;
}

void EffacerEcran(unsigned long c)
{
	if (num_ecran==0)
	{
		XSetWindowBackground(display,ecran[num_ecran],c);
		XClearWindow(display,ecran[num_ecran]);
	}
	else 
	{ 
		XSetForeground(display,gc,c);
		XFillRectangle(display,ecran[num_ecran],gc,0,0,X_fen,Y_fen);
		XSetForeground(display,gc,couleur_dess);
	}
	XFlush(display);
}

void EcrireTexteC(int x,int y,char *texte,int mode,unsigned long c)
{
	if (mode<0||mode>2) return;
	XSetFont(display,gc,f[mode]);
	XSetForeground(display,gc,c);
	XDrawString(display,ecran[num_ecran],gc,x,y,texte,strlen(texte));
	XSetForeground(display,gc,couleur_dess);
	XFlush(display);
}

void EcrireTexte(int x,int y,char *texte,int mode)
{
	if (mode<0||mode>2) return;
	XSetFont(display,gc,f[mode]);
	XDrawString(display,ecran[num_ecran],gc,x,y,texte,strlen(texte));
	XFlush(display);

}
#ifdef HAVE_XPM
void SauverImage(char * file,int x,int y,int l,int h)
{
	XEvent report;
	Pixmap p1=0;
	p1=XCreatePixmap( display , DefaultRootWindow(display), X_fen , Y_fen , DefaultDepth(display,screen) );
	XCopyArea(display,ecran[num_ecran],p1,gc,x,y,l,h,0,0);
	XpmWriteFileFromPixmap(display,file,p1,0,NULL);
	if (p1) XFreePixmap(display,p1);
	while(XCheckWindowEvent(display,ecran[0],ExposureMask,&report));
	while(XCheckTypedEvent(display,GraphicsExpose,&report));
	while(XCheckTypedEvent(display,NoExpose,&report));
}
#endif

int ChargerImage(char *file,int x,int y,int xx,int yy,int l,int h)
{
	XEvent report;
	Pixmap p1=0,p1mask=0;
	int wi,hi;
	if (!_chargerimage(file, &wi,&hi,&p1 , &p1mask,display,gc,screen)) return 0;

	//XpmReadFileToPixmap(display,ecran[num_ecran],file,&p1,&p1mask,NULL);

	XSetClipMask(display,gc,p1mask);
	XSetClipOrigin(display,gc,x,y);
	XCopyArea(display,p1,ecran[num_ecran],gc,xx,yy,l,h,x,y);

	XSetClipMask(display,gc,None);
	if (p1) XFreePixmap(display,p1);
	if (p1mask) XFreePixmap(display,p1mask);

	//XFlush(display);

	while(XCheckWindowEvent(display,ecran[0],ExposureMask,&report));
	while(XCheckTypedEvent(display,GraphicsExpose,&report));
	while(XCheckTypedEvent(display,NoExpose,&report));    
	return 1;

}

void ChargerImageFond(char *file)
{ 
	XSetWindowAttributes att;
	Pixmap pbackground=0,pmask=0;
	int i=num_ecran;
	int x,y;
	if (i<0 || i>NB_PIXMAP) return ;

	switch(i)
	{
		case 0 :
			//XpmReadFileToPixmap(display,ecran[i],file,&pbackground,&pmask,NULL);
			_chargerimage(file, &x,&y,&pbackground , &pmask,display,gc,screen);
			att.background_pixmap=pbackground;
			XChangeWindowAttributes(display,ecran[i],CWBackPixmap,&att);
			XClearWindow(display,ecran[i]);

			if (pbackground) XFreePixmap(display,pbackground);
			if (pmask) XFreePixmap(display,pmask);
			XFlush(display);
			break;
		default:
			ChargerImage(file,0,0,0,0,X_fen,Y_fen);
	} 
}

int TailleChaineEcran(char *t,int mode)
{
	if (mode<0||mode>2) return -1;
	else return XTextWidth(s[mode],t,strlen(t));
}
int TailleSupPolice(int mode)
{
	if (mode<0||mode>2) return -1;
	return s[mode]->ascent;
}

int TailleInfPolice(int mode)
{
	if (mode<0||mode>2) return -1;
	return s[mode]->descent;
}


void CopierZone(int src,int dst,int ox,int oy,int L,int H,int dx,int dy)
{
	XEvent report;
	XCopyArea(display,ecran[src],ecran[dst],gc,ox,oy,L,H,dx,dy);
	XFlush(display);
	while(XCheckWindowEvent(display,ecran[0],ExposureMask,&report));
	while(XCheckTypedEvent(display,GraphicsExpose,&report));
	while(XCheckTypedEvent(display,NoExpose,&report));
}


void CacherFenetre()
{
	XUnmapWindow(display,ecran[0]);
	XFlush(display);
};

void AfficherFenetre(void)
{
	XMapWindow(display,ecran[0]);
	XFlush(display);
}


unsigned long CouleurParComposante(unsigned char r, unsigned char v,unsigned char b)
{
	/* on suppose qu'on est en True Color */
	/* C'est a ameliorer !!!              */
	/* XColor c;
	   c.red=r;
	   c.red<<=8;
	   c.green=v;
	   c.green<<=8;
	   c.blue=b;
	   c.blue<<=8;
	   XAllocColor(display,DefaultColormap(display,screen),&c);
	   return c.pixel;*/
	unsigned long cr=r,cg=v,cb=b;
	return (cr<<16)|(cg<<8)|cb;
}


unsigned long Microsecondes()
{
	struct timeval t;
	gettimeofday(&t, NULL);
	return t.tv_usec+t.tv_sec*1000000;
}


/*
   int souris(int *X,int *Y)
   {
   XEvent r;
   if (XCheckWindowEvent(display,ecran[0],PointerMotionMask,&r))
   {*X=r.xmotion.x;*Y=r.xmotion.y;return 1;}
   return 0;
   }
   */



void SourisPosition()
{
	int x,y,rx,ry;
	unsigned int etat;
	Window a,b;
	XQueryPointer(display, ecran[0], &a, &b, &rx, &ry, &x, &y, &etat);
	_X=x;_Y=y;
}

int _longueur()
{
	return XQLength(display);
}

int SourisCliquee()
{
	XEvent r;
	if (XCheckWindowEvent(display,ecran[0],ButtonPressMask,&r))
	{
		_X=r.xbutton.x;
		_Y=r.xbutton.y;
		return 1;
	}
	return 0;
}
int SpriteLibre()
{
	int i;
	for(i=0;i<N;i++) if (S_alloue[i]==0) return i;
	return -1;
}

int ChargerSprite(char *file)
{
	Pixmap p1=0,p1mask=0;
	int nu,w,h;
#ifdef HAVE_XPM
	XpmAttributes a;
	a.valuemask=XpmSize;
#endif
	nu=SpriteLibre();
	if (nu==-1) return -1;
	S_alloue[nu]=1;
	if (!_chargerimage(file, &w,&h,&p1 , &p1mask,display,gc,screen))
		//if (XpmReadFileToPixmap(display,ecran[num_ecran],file,&p1,&p1mask,&a)!=0)
	{
		S_alloue[nu]=0;
		return -1;
	}
	S[nu].posx=-1;
	S[nu].posy=-1;
	S[nu].etat=0;
	//S[nu].tx=a.width;
	//S[nu].ty=a.height;
	S[nu].tx=w;
	S[nu].ty=h;
	S[nu].s=p1;
	S[nu].smask=p1mask;
	S[nu].sauvegarde=0;
	S[nu].etat=0;

	return nu+1;
}

void AfficherSprite(int n,int x,int y)
{
	Pixmap p;
	n--;
	if (n<0||n>=N) return;
	if (S_alloue[n]!=1) return;	
	/*	if ((S[n].etat)==0)
		{
		p=XCreatePixmap( display , DefaultRootWindow(display), S[n].tx ,S[n].ty  , DefaultDepth(display,screen) );
		XCopyArea(display,ecran[num_ecran],p,gc,x,y,S[n].tx,S[n].ty,0,0);
		S[n].sauvegarde=p;


		}*/

	/* restitue la zone */

	//XSetClipMask(display,gc,None);
	//if (S[n].etat!=0) XCopyArea(display,S[n].sauvegarde,ecran[num_ecran],gc,0,0,S[n].tx,S[n].ty,S[n].posx,S[n].posy);

	//XCopyArea(display,ecran[num_ecran],S[n].sauvegarde,gc,x,y,S[n].tx,S[n].ty,0,0);
	if (S[n].smask!=0) {
		XSetClipMask(display,gc,S[n].smask);
		XSetClipOrigin(display,gc,x,y);
	}
	XCopyArea(display,S[n].s,ecran[num_ecran],gc,0,0,S[n].tx,S[n].ty,x,y);
	S[n].posx=x;
	S[n].posy=y;
	S[n].etat=1;
	XFlush(display);
	XSetClipMask(display,gc,None);
}

/*void EffacerSprite(int n)
{
	n--;
	if (S[n].etat!=0) XCopyArea(display,S[n].sauvegarde,ecran[num_ecran],gc,0,0,S[n].tx,S[n].ty,S[n].posx,S[n].posy);
	S[n].etat=0;
}*/

void LibererSprite(int n)
{
	n--;
	if (n<0||n>=N) return;
	if (S_alloue[n]!=1) return;
	if (S[n].s>0) XFreePixmap(display,S[n].s);
	if (S[n].smask>0) XFreePixmap(display,S[n].smask);
	if (S[n].sauvegarde>0) XFreePixmap(display,S[n].sauvegarde);
	S_alloue[n]=0;
}

