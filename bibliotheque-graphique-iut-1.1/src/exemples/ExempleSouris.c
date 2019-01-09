#include<stdio.h>
#include<graph.h>

int main(void)
{
	int x=100,y=100,x1,y1;
	InitialiserGraphique();
	CreerFenetre(700,100,500,500);
	EffacerEcran(CouleurParNom("white"));
	while(!SourisCliquee());
	x=_X;
	y=_Y;
	while(1)
	{
		if (SourisCliquee()) 
		{
			DessinerSegmentC(_X,_Y,x,y,CouleurParComposante(rand()%256,rand()%256,rand()%256));    
			x=_X;
			y=_Y;
		}
		if (ToucheEnAttente()) break;
	}
	FermerGraphique();

}
