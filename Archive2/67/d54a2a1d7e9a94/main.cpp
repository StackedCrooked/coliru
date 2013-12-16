#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char lettre; // Stocke la lettre proposée par l'utilisateur (retour du scanf)
    char motSecret[] = "MARRON"; // C'est le mot à trouver
    int coupsRestants = 4; // Compteur de coups restants (0 = mort)

    /*******************/
	printf("Bienvenue dans le Jeu Pendu !\n\n");
	/*******************/	
	printf("Il vous reste %d coups a jouer\n", coupsRestants);
	printf("Quel est le mot secret ? \n");
	/*******************/
	/*Maintenant qu'on a affiché ce qu'il fallait, on va demander au joueur de saisir une lettre :	*/
	printf("Proposez une lettre : \n");
	//scanf ("%s",&lettre);
	lettre = getchar(); /* l'utilisateur doit alors taper au moins un caractère du clavier*/
}