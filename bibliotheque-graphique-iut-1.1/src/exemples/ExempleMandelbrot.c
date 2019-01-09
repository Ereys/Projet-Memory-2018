#include<stdio.h>
#include<stdlib.h>
#include<graph.h>
#define N 256     /* nombre d'iteration et de couleurs donc   */

/* listes des fonctions */

void mise_a_jour_coef();
int mandelbrot();
void dessine_mandelbrot();
void init_palette();
void init_parametre();
typedef struct R
{
	int x,y,width,height;
} R;
/* variables globales pour X */



/* variables globales pour la fractale */

double  ax,bx,ay,by;         /* coefficient de changement de repere       */
double xr0,xr1,yr0,yr1,tmp;  /* borne du domaine reel [xr0,xr1]*[yr0,yr1] */
unsigned long palette[N];    /* couleurs pour le dessin de la fractale    */ 
R Rcourant,Rancien;



int main(int nbarg,char *arg[])
{
	int display_width, display_height;  /* taille de l'ecran (root window)  */
	int width, height;                  /* taille de la fenetre             */
	int x=0, y=0;                       /* position de la fenetre           */
	int Xold,Yold;
	XColor couleur;
	int ancx,ancy;
	int x0,y0,x1,y1;                    /* coordonnee pour le zoom          */
	int pb;
	int clic;
	int to;
	/* Initialiser la taille de la fenetre en fonction de la taille de l'ecran */
	if (nbarg!=1)
	{
		width=atoi(arg[1]);
		height=atoi(arg[2]);
	}
	else {
		width  = 550;
		height = 550;
	}

printf("Utiliser la souris pour zoomer sur une partie de l'ensemble\n");
	InitialiserGraphique();
	CreerFenetre(0,0,width,height);
	init_parametre();
	dessine_mandelbrot(width,height);
	while(1)
	{
		if (SourisCliquee())
		{
			if (clic==0)
			{
				Xold=_X;
				Yold=_Y;
				Rcourant.x=_X;
				Rcourant.y=_Y;
				x0=Rcourant.x;
				y0=Rcourant.y;
				xr0=ax*_X+bx;
				yr0=ay*_Y+by;
				Rcourant.width=Rcourant.height=0;
				ChoisirModeDessin(2);
				DessinerRectangle(Rcourant.x,Rcourant.y,Rcourant.width,Rcourant.height);
				ChoisirModeDessin(0);
				clic=1;
			}
			else
			{
				xr1=ax*_X+bx;
				yr1=ay*_Y+by;
				if (xr1<xr0) {tmp=xr1;xr1=xr0;xr0=tmp;}
				if (yr1<yr0)  {tmp=yr1;yr1=yr0;yr0=tmp;}
				printf("%f:%f:%f:%f\n",xr0,xr1,yr0,yr1);
				dessine_mandelbrot(width,height);
				clic=0;
			}
		}
		if (clic==1)
		{
			SourisPosition();
			if (_X!=Xold||_Y!=Yold)
			{
				Rancien=Rcourant;
				x1=_X;
				y1=_Y;
				Xold=_X;
				Yold=_Y;
				if (x1<x0) {Rcourant.x=x1;Rcourant.width=x0-x1;} else  {Rcourant.x=x0; Rcourant.width=x1-x0; }
				if (y1<y0) {Rcourant.y=y1;Rcourant.height=y0-y1;} else  {Rcourant.y=y0; Rcourant.height=y1-y0; }


				ChoisirModeDessin(2);
				DessinerRectangle(Rcourant.x,Rcourant.y,Rcourant.width,Rcourant.height);
				DessinerRectangle(Rancien.x,Rancien.y,Rancien.width,Rancien.height);
				ChoisirModeDessin(0);
			}
			//  XDrawRectangles(display,win,gc_xor,&Rcourant,1);
			//XDrawRectangles(display,win,gc_xor,&Rancien,1);
		}
		if (ToucheEnAttente())
		{
			to=Touche();
			if (to=='i')
			{
				init_parametre();
				dessine_mandelbrot(width,height);
			}
			if (to=='q')
			{
				FermerGraphique();
				return;
			}
		}


	}
	Touche();
	FermerGraphique();




} 



void mise_a_jour_coef(int dimx,int dimy)
{

	bx=xr0;
	ax=(xr1-bx)/dimx;
	by=yr0;
	ay=(yr1-by)/dimy;

}

int mandelbrot(double x,double y)
{
	int n=0;
	double mod=0;
	double x1,y1,x0=0,y0=0;

	while (n<N-1&&mod<=4)
	{
		x1=x0*x0-y0*y0+x;
		y1=2*x0*y0+y;
		mod=x1*x1+y1*y1;
		x0=x1;
		y0=y1;
		n++;
	}
	return n;
}

void dessine_mandelbrot(int dimx,int dimy)
{
	int i,j,n;
	mise_a_jour_coef(dimx,dimy);
	for (i=0;i<dimx;i++)
	{
		for(j=0;j<dimy;j++)
		{
			n=mandelbrot(ax*i+bx,ay*j+by);
			//printf("%d\n",n);
			ChoisirCouleurDessin(palette[n]);
			DessinerPixel(i,j);
		}
	}

}

void init_palette()
{
	int  n;
	unsigned short i;
	int r,v,b;
	int col=0;
	v=255;
	for (n=0;n<64;n++)
	{ 
		//c.red = (255)*256;
		//c.green = 16*n*256;
		//c.blue = 0;
		//i=XAllocColor(display,pal,&c);
		//printf("retou = %d : val = %d\n",i,c.pixel);
		palette[n]=CouleurParComposante(255,10*4*n,0);
	}
	for (n=0;n<64;n++)
	{ 
		//	c.red = (256-4*n)*256;
		//	c.green = (255)*256;
		//	c.blue = 16*n*256;
		//	i=XAllocColor(display,pal,&c);
		//printf("retou = %d : val = %d\n",i,c.pixel);
		palette[n+64]=CouleurParComposante( 10*(255-4*n),(255), 10*4*n);
	}

	for (n=0;n<64;n++)
	{
		//	c.red = 0;
		//	c.green = (256-4*n)*256;
		//	c.blue = (255)*256;
		//	i=XAllocColor(display,pal,&c);
		//printf("retou = %d : val = %d\n",i,c.pixel);
		palette[n+128]=CouleurParComposante(0,10*(255-4*n),255);

		//c.pixel;
	}
	for (n=0;n<64;n++)
	{ 
		//c.red = (n*4)*256;
		//c.green = (n*4)*256;
		//
		/*c.blue=(256-4*n);
		  c.red=(256-4*n)*256,
		  c.green=0;
		  */
		//  c.blue = ((63-n)*4)*256;
		//	i=XAllocColor(display,pal,&c);
		//printf("retou = %d : val = %d\n",i,c.pixel);
		palette[n+192]=CouleurParComposante(10*(255-4*n),10*(255-4*n),0);
	} 


	//for (i=0;i<=255;i++) palette[i]=CouleurParComposante(10*i,10*i,10*i);
	//for(i=0;i<=255;i++)
	//  {

	//c.red=i*i*25r;
	//	c.blue=i*200;
	//	c.green=500*i;

	//c.blue=0 ;
	//c.green=0;
	//c.red=i*256;
	//n=XAllocColor(display,pal,&c);
	// printf("retou = %d : val = %d\n",n,c.pixel);
	//palette[i]=c.pixel;

	// printf("%ld-",palette[i]);

	// }   

}


void init_parametre()
{
	yr0=-1.5;
	xr0=-2;
	yr1=1.5;
	xr1=1.5;
	//xr0=-2;yr1=xr1=2;
	init_palette();
}
