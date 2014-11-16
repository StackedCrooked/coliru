#include <stdio.h>
int main ()
{
  int J,I,M[100][100],N,C,X,K;
  
  printf ("\n\nInserisci la dimesione della matrice....");
  scanf("%d", &N);
  
  for (I=0;I<N;I++)
  {
      for (J=0;J<N;J++)
      {
          printf ("\n\nInserisci il valore della matrice....");
          scanf("%d",&M[I][J]);
      }
  }
  X=I;
  K=J;
  C=0;
  
  do {
        if (M[I][K]==M[J][X])
            {
                I++;
                J++;
                C++;
            }
            else 
            {
                X++;
                K++;
                C=0;
            }
            }while (C=0);
            {
                printf("Hai trovato una parola sia nelle righe che nelle colonne..");
            } 
}