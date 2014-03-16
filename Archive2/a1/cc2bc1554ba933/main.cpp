/ / En-tête fichier 
# ifndef EXAMPLE_H 
# define EXAMPLE_H 
/ / fonction incluse dans plusieurs fichiers source doit être en ligne 
en ligne  int somme ( int a, int b )  
{ 
    retourner un + b ; 
} 
# endif
 
/ / Fichier source # 2 
# include "example.h" 
int un ( ) 
{ 
    retour somme ( 1 , 2 ) ; 
}
 
/ / Fichier source # 1 
# include "example.h" 
int b ( ) 
{ 
    retour somme ( 3 , 4 ) ; 
}