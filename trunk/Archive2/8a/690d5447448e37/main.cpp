#include <stdio.h>
2#include <stdlib.h>
3
4int main(int argc, char *argv[])
5{
6  int nombreDeVies = 5; // Au départ, le joueur a 5 vies
7  
8  printf("Vous avez %d vies\n", nombreDeVies);
9  printf("**** B A M ****\n"); // Là il se prend un grand coup sur la tête
10  nombreDeVies = 4; // Il vient de perdre une vie !
11  printf("Ah desole, il ne vous reste plus que %d vies maintenant !\n\n", nombreDeVies);
12  
13  return 0;
14}