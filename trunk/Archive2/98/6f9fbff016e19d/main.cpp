#include <stdio.h>
#include <stdlib.h>
#include <math.h>

 int main()
 {
     int nombre1 = 0;
     int nombre2 = 0;
     int resultat = 0;
     
  printf("Ecrire le premier chiffre\n");
  scanf("%d", &nombre1);
  
  printf("Ecrire le deuxieme chiffre\n");
  scanf("%d", &nombre2);
  
  resultat = nombre1 + nombre2;
  
  printf("Le resultat est : %d \n", resultat);
  return 0;
 }
 