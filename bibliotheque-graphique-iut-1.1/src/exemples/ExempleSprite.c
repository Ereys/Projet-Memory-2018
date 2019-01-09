#include<stdio.h>
#include<stdlib.h>
#include<graph.h>


int main()
{
	int t;
	int dir;
	int spr[6];
	int spl[6];
	char nom[500];
	int inc=10,i;
	int x=10,y=420;
	int dx=1,dy;
	int ok=1;
	InitialiserGraphique();
	CreerFenetre(0,0,800,500);
	ChoisirEcran(2);
	sprintf(nom,"%s/%s",EXEMPLES_IMAGES_DIR,"arctis2.jpg");
	ChargerImageFond(nom);
	//ChargerImageFond("./images/walks-1.png");
	for (i=0;i<6;i++)
	{
		sprintf(nom,"%s/nouveau%0d.xpm",EXEMPLES_IMAGES_DIR,i);
		if ((spr[i]=ChargerSprite(nom))==-1)
		{

		sprintf(nom,"%s/walk-%d.png",EXEMPLES_IMAGES_DIR,i);
		spr[i]=ChargerSprite(nom);
		}

		sprintf(nom,"%s/nouveauinverse%0d.xpm",EXEMPLES_IMAGES_DIR,i);
		if ((spl[i]=ChargerSprite(nom))==-1)
		{
		sprintf(nom,"%s/walks-%d.png",EXEMPLES_IMAGES_DIR,i);
		spl[i]=ChargerSprite(nom);
		}
		
	}
	ChoisirEcran(1);
	CopierZone(2,1,0,0,800,500,0,0);
	AfficherSprite(spr[0],x,y);
	CopierZone(1,0,0,0,800,500,0,0);
	dir=1;
	i=0;
	while(ok)
	{
		t=Touche();
		switch(t)
		{
			case XK_Left : 
				x-=inc;
				dir=-1;
				break;
			case XK_Right:
				x+=inc;
				dir=1;
				break;
			default:ok=0;
		}
		ChoisirEcran(1);
		CopierZone(2,1,0,0,800,500,0,0);

		if (i>5) i=0;
		if ((x+64)>800) x=800-64;
		else
			if (x<0) x=0;

		if (dir==1)
			AfficherSprite(spr[i],x,y);
		else
			AfficherSprite(spl[i],x,y);
		CopierZone(1,0,0,0,800,500,0,0);
		i=i+1;
	}
	FermerGraphique();
}
