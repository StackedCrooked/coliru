#include <stdio.h>
#include <stdlib.h>
 
int main()
{     int bien ;
     printf("******************************************************************\n");
     printf("*************** Bienvenue dans Happy Birthday 1.0 !!!! ***************\n");
     printf("******************************************************************\n\n\n");
     printf("Bon nous allons commencer !!\n\n");
     printf("Comment allez vous ? \n\n");
     printf("1. Je vais bien .\n\n");
     printf("2. Je ne vais pas bien .\n\n");
     printf("tapez un des 2 chiffres :\t");
     scanf("%d", &bien);
 
     switch (bien)
    { case 1 :
      printf("Moi aussi je vais bien ! :D\n\n");
      break;
      case 2 :
      printf("Moi je vais bien.(\n\n");
      printf("La Beta 1 de 'HB' n'a pas encore la possibilite de vous demander pourquoi ?\n\n");
      break;
      default :
      printf("Vous n'avez pas tape le bon chiffre =) recommencer svp =)\n\n\n");
      break;
      }
 
 int jour, mois, ans;
  printf ("1.Quel jour on est ?\n");
  scanf ("%d", &jour);
  printf ("1.Quel mois on est ?\n");
  scanf ("%d", &mois);
  printf ("1.Quelle annee on est ?\n");
  scanf ("%d", &ans);
  printf ("D'accord, nous sommes donc le : %d/%d/%d\n\n", jour, mois, ans);
 
int jouranniversaire, moisanniversaire, anneeaniversaire ;
  printf ("1.Quel jour etes vous nee ?\n");
  scanf ("%d", &jouranniversaire);
  printf ("1.Quel mois etes vous nee  ?\n");
  scanf ("%d", &moisanniversaire);
  printf ("1.Quelle annee on est ?\n");
  scanf ("%d", &anneeaniversaire);
  printf ("D'accord, votre anniversaire est donc le : %d/%d/%d\n\n", jouranniversaire, moisanniversaire, anneeaniversaire );
 
  if (jouranniversaire == jour && moisanniversaire == mois && anneeaniversaire == ans)
{
  printf("\n\n\n");
 
     printf("**   **|*****        ~~     ~~            \n");
     printf("**   **|*    *     __||_____||__                      \n");
     printf("**   **|*     *    OOOOOOOOOOOOO                     \n");
     printf("*******|******     ~~~~~~~~~~~~~                        \n");
     printf("*******|******     \\          //                         \n");
     printf("**   **|*     *     ~~~~~~~~~~~                        \n");
     printf("**   **|*    *      \\________//                       \n");
     printf("**   **|*****                              \n\n\n");
 
 
printf(" JOYEUX ANNIVERSAIRE !!!!!!!!!!!!\n");
}
else
{
  printf("Dommage ce n'est pas votre anniversaire aujourd'hui, revene une autre fois, merci !!! =) \n\n");
}
 
 
  system("pause");
 
    return 0;
}