/* sscanf example */
#include <stdio.h>

int main ()
{
  char sentence []="2011.1.0033.0271-8;Renan Collienne Braga Alves";
  char mat [20];
  char name [50];
  int i;

  sscanf (sentence,"%s;%s",mat,name);
  printf ("%s -> %s\n",mat,name);
  
  return 0;
}