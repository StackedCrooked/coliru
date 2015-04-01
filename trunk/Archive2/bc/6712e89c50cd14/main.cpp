#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include "somme.h"

int main()
{
    int tableau[5] = { 50,12,32,64,85};
    
    printf( "La somme des valeurs du tableau est de : %d.", sommeTableau( tableau, 5 ) );
    
    return 0;
}

int sommeTableau( int tableau[], int taille ) 
{
    int somme = 0;
    for ( int i = 0 ; i < taille ; i++ ) {
       somme += tableau[i];
    }
    return somme;
}