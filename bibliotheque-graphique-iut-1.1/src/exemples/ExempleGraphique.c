#include<graph.h>
#include<math.h>
#include<time.h>
#include<stdio.h>
#define ra 30

#define tx 650
#define ty 500
int pt[2][100][100];

typedef struct point
{float x,y;} point ;

void ressort()
{
	point m={tx/2,10};
	point ma=m;
	time_t t1,t2;
	point m1={100,100};
	point m2={100,200};
	point m1d={0,0};
	point m2d={0,0};
	point mdd,m1dd,m2dd;
	point u1,u2;
	float n1,n2;
	float k1=0.5,k2=0.5   ;
	float l1=50,l2=100,l=0.1;
	float mm1=2,mm2=0.5;
	float F1,F2;
	float g=9.81;
	float dt=0.5;
	int i,j;
	unsigned long cn,cb,temps,temporisation=50000;
	cn=CouleurParNom("red");
	cb=CouleurParNom("white");
	ChoisirCouleurDessin(cn);
	SourisPosition();
	m.x=_X;m.y=_Y;
	ma=m;
	DessinerSegment(m.x,m.y,m1.x,m1.y);
	DessinerSegment(m1.x,m1.y,m2.x,m2.y);
	DessinerArc(m1.x-ra/2,m1.y-ra/2,ra,ra,0,360);
	DessinerArc(m2.x-ra/2,m2.y-ra/2,ra,ra,0,360);
	while(!SourisCliquee())
	{
		SourisPosition();
		m.x=_X;m.y=_Y;

		temps=Microsecondes()+temporisation;
		while(Microsecondes()<temps);
		//for (j=0;j<=3;j++){
		//     for (i=0;i<=1000000;i++);}
		ChoisirCouleurDessin(cb);
		DessinerSegment(ma.x,ma.y,m1.x,m1.y);
		DessinerSegment(m1.x,m1.y,m2.x,m2.y);



		DessinerArc(m1.x-ra/2,m1.y-ra/2,ra,ra,0,360);
		DessinerArc(m2.x-ra/2,m2.y-ra/2,ra,ra,0,360);

		u1.x=m1.x-m.x;
		u1.y=m1.y-m.y;
		u2.x=m2.x-m1.x;
		u2.y=m2.y-m1.y;

		n1=sqrt(u1.x*u1.x+u1.y*u1.y);
		n2=sqrt(u2.x*u2.x+u2.y*u2.y);

		F1=k1*(n1-l1);
		F2=k2*(n2-l2);

		m2dd.x=(1/mm2)*(-F2*u2.x/n2-l*m2d.x);

		m2dd.y=g+(-(F2/mm2)*u2.y/n2)-l/mm2*m2d.y;;

		m1dd.x=(1/mm1)*(-F1*u1.x/n1+F2*u2.x/n2-l*m1d.x);
		m1dd.y=g+(1/mm1)*(-F1*u1.y/n1+F2*u2.y/n2)-l/mm1*m1d.y;

		//m1dd.x=(1/mm1)*(-F1*u1.x/n1-l*m1d.x);
		//m1dd.y=g+(-(F1/mm1)*u1.y/n1)-l/mm1*m1d.y;

		m1d.x+=m1dd.x*dt;
		m1d.y+=m1dd.y*dt;

		m2d.x+=m2dd.x*dt;
		m2d.y+=m2dd.y*dt;

		m1.x+=m1d.x*dt;
		m1.y+=m1d.y*dt;

		m2.x+=m2d.x*dt;
		m2.y+=m2d.y*dt;

		ChoisirCouleurDessin(cn);
		DessinerSegment(m.x,m.y,m1.x,m1.y);
		DessinerSegment(m1.x,m1.y,m2.x,m2.y);
		DessinerArc(m1.x-ra/2,m1.y-ra/2,ra,ra,0,360);
		DessinerArc(m2.x-ra/2,m2.y-ra/2,ra,ra,0,360);
		ma=m;

	}

}
void affiche()
{
	int i,j;

	for(i=0;i<=80;i++)
	{
		for(j=0;j<=80;j++)
		{

			if (i!=80) DessinerSegment(pt[0][i][j],pt[1][i][j],pt[0][i+1][j],pt[1][i+1][j]);
			if (j!=80) DessinerSegment(pt[0][i][j],pt[1][i][j],pt[0][i][j+1],pt[1][i][j+1]); 
		}
	}

}

void calcul()
{
	int i,j;
	float X,Y,Z,XX,YY,ZZ,l,stepx=0.1,stepy=0.1;
	//float d[3]={cos(M_PI/6),-1,sin(M_PI/6)};
	float d[3]={1,1,0.5};
	for (i=0,X=-4;X<4;X=X+stepx,i++)
	{
		for(j=0,Y=-4;Y<4;Y=Y+stepy,j++)
		{
			if (X==0) XX=3; else XX=sin(3*X)/(X);
			if (Y==0) YY=3;else YY=sin(3*Y)/(Y);
			Z=(XX*YY);

			XX=50*X;
			YY=40*Y;
			ZZ=-30*Z;

			l=-XX/d[0];
			XX=YY+l*d[1];

			YY=ZZ+l*d[2];
			pt[0][i][j]=XX+tx/2;
			pt[1][i][j]=YY+ty/2+50;

		}
	}

}
void ballon()
{
	int d=40;
	int x=100,y=100;
	int xold,yold;
	int dx=1,dy=0;
	int t;
	unsigned long r=CouleurParNom("green");
	unsigned long w=CouleurParNom("white");
	struct timespec to={0,1};
	unsigned long t1,t2;

	ChoisirModeDessin(1);
	DessinerArcC(x,y,d,d,0,360,r);
	//  RemplirArc(x,y,d,d,0,360,r);
	while ((t=Touche())!=' ');
	t1= Microsecondes();
	xold=x;
	yold=y;
	ChoisirCouleurDessin(r);
	while(1)
	{

		//DessinerArc(x,y,d,d,0,360);
		//RemplirArc(x,y,d,d,0,360,r);
		if (ToucheEnAttente()) {
			t=Touche();
			switch(t){
				case XK_Up: dy=-1;dx=0;
							break;
				case XK_Down:dy=1;dx=0;
							 break;
				case XK_Left: dy=0;dx=-1;
							  break;
				case XK_Right:dy=0;dx=1;
							  break;
				case 'q':return;
			}
		}

		x+=dx;y+=dy;

		if (x<0) x=tx;else {if (x>tx) x=0;}
		if (y<0) y=ty;else {if (y>ty) y=0;}
		while ((Microsecondes()-t1)<10000);
		t1=Microsecondes();
		// RemplirArc(x,y,d,d,0,360,r);
		if (xold!=x||yold!=y)
		{
			DessinerArc(xold,yold,d,d,0,360);
			DessinerArc(x,y,d,d,0,360);
			xold=x;
			yold=y;
		}

	}
}

int main(void)

{
	int x,y;
	int i,j;
	unsigned long couleur=0;
	int a,mode;
	float teta;

	char * s="appuyez sur une touche pour commencer";
	char *s1="Super cette bibliotèque!!!";
	char *s2="et pour changer d'écrans";

	InitialiserGraphique();
	CreerFenetre(0,0,tx,ty);
	//affiche_fenetre();
	//while((x=touche())!=XK_space) printf("%x:%c\n",x,x);
	EffacerEcran(CouleurParNom("white"));
	ChoisirCouleurDessin(CouleurParNom("black"));
	
	y=ty/2;
	x=(tx-TailleChaineEcran(s,1))/2;
	EcrireTexte(x,y,s,1);
	y=ty/2+50;
	x=(tx-TailleChaineEcran(s2,1))/2;
	EcrireTexte(x,y,s2,1);
	Touche();
	EffacerEcran(CouleurParNom("white"));
	ChoisirCouleurDessin(CouleurParNom("red"));
	RemplirRectangle(50,50,100,100);
	ChoisirCouleurDessin(CouleurParNom("green"));
	RemplirRectangle(75,75,100,100);
	ChoisirCouleurDessin(CouleurParNom("blue"));
	RemplirRectangle(100,100,100,100);
	DessinerArc(200,200,200,200,90,90);
	ChoisirCouleurDessin(CouleurParNom("yellow"));
	RemplirArc(300,300,200,200,45,270);
	Touche();
	EffacerEcran(CouleurParNom("white"));
	calcul();
	ChoisirCouleurDessin(CouleurParNom("black"));
	affiche();
	Touche();
	//sauve_image("toto.xpm",0,0,tx,ty);
	//cache_fenetre();
	//printf("fenetre cachee pendant 2 secondes\n");
	//sleep(2);

	/*
	EffacerEcran(CouleurParNom("blue"));
	EcrireTexte(10,20,s1,0);
	EcrireTexte(10,40,s1,1);
	EcrireTexte(10,70,s1,2);//CouleurParNom("green"),2);

	//EcrireTexteC(10,70,s1,CouleurParNom("green"),2);
	AfficherFenetre();
	Touche();

	ChargerImage("flocon.xpm",100,100,0,0,200,200);
	Touche();
	ChoisirEcran(1);
	EffacerEcran(CouleurParNom("green"));  
	ChoisirCouleurDessin(CouleurParNom("blue"));
	EcrireTexte(50,40,"C'est Beau !!!",1);
	CopierZone(1,0,0,0,200,200,300,100);
	ChoisirEcran(0);
	Touche();
	ChoisirCouleurDessin(CouleurParNom("yellow"));
	DessinerArc(300,300,200,200,0,360); 
	Touche();
	EffacerEcran(CouleurParNom("white"));
	ChargerImageFond("flocon.xpm");
	Touche();
	*/
		EffacerEcran(CouleurParNom("white"));
	//ChargerImageFond("flocon.xpm");
	y=ty/2;
	x=(tx-TailleChaineEcran("fleches pour deplacer le cercle",2))/2;

	ChoisirCouleurDessin(CouleurParNom("blue"));
	EcrireTexte(x,y,"fleches pour deplacer le cercle",2);
	y=ty/2+40;
	x=(tx-TailleChaineEcran("espace pour commencer",2))/2;

	EcrireTexte(x,y,"espace pour commencer",2);

	y=ty/2+80;
	x=(tx-TailleChaineEcran("q pour quitter",2))/2;
	EcrireTexte(x,y,"q pour quitter",2);
	ballon();
	ChoisirModeDessin(0);
	EffacerEcran(CouleurParNom("white")); 
	while(SourisCliquee());
	ressort();
	FermerGraphique();
	printf("Bye !!!!\n");
	//InitialiserGraphique();
	//CreerFenetre(50,10,tx,ty);
	//EffacerEcran(CouleurParNom("red"));
	//Touche();

}






void rotation(float *x,float *y,float *z,float teta,int mode)
{float xx,yy,zz;
	float co=cos(teta),so=sin(teta);
	switch(mode)
	{
		case 0 : /* rotation autour de z */
			xx=co**x+*y*so;
			yy=-so**x+*y*co;
			*x=xx;
			*y=yy;
			break;
		case 1:
			xx=*x*co+*z*so;
			zz=-*x*so+*z*co;
			*x=xx;
			*y=yy;
	}

}
