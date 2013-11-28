#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char lettre[1] ; // Stocke la lettre proposée par l'utilisateur (retour du scanf)
    int coupsRestants = 4; // Compteur de coups restants (0 = mort)
    //    char motSecret[] = "MARRON"; // C'est le mot à trouver
    //int i = 0; // Une petite variable pour parcourir les tableaux
   // int l=0;
	
	printf("Bienvenue dans le Pendu !\n\n");
		
	printf("\n\nIl vous reste %d coups a jouer", coupsRestants);
	printf("\nQuel est le mot secret ? ");
	
	
	/*Maintenant qu'on a affiché ce qu'il fallait, on va demander au joueur de saisir une lettre :	*/
	printf("\nProposez une lettre : ");
	gets(lettre);	

	
}