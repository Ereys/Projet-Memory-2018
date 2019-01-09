#ifndef jeu_h
#define  jeu_h

#include "graph.h"


#define TABMAX 15



int RemplissageMap(int nbcartes, int longtab, int largtab,int map[TABMAX][TABMAX]);
int Initialiser0(int longtab, int largtab,int map[TABMAX][TABMAX]);								/*Signatures*/
int alea(int min, int max);
void AfficherCartes(int a,int b,int mx, int my);
int FlipCard(int Taille1,int Taille2, int nbpaires, int map[TABMAX][TABMAX],int mx,int my, int *paires);
int Triche(int Taille1,int Taille2,int mx, int my, int map[TABMAX][TABMAX]);
void Cacher();
void Timer();
void ClearClick();

 #endif