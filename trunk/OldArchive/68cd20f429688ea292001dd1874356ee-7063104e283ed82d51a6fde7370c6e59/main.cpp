#include <stdio.h>
#include <limits.h>

int main(void)
{
  int entier, i = 0;
  long puiss;

  printf("Ce programme calcule des puissances\n\n");
  printf("Indiquer un entier au moins egal a 2 : ");
  scanf("%d", &entier);
  puiss = 1;
  while (puiss <= LONG_MAX/entier)
    {
      puiss *= entier;
      i++;
      printf("%d e puissance : %ld\n", i, puiss);
    }
  return 0;
}