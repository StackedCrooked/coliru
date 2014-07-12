#include <stdio.h> 
#include <stdlib.h>
#include <math.h>

int T[10],i,x ;
void remp ()
{
  for (i=0 ; i<10 ; i++)
  {
    printf ("\nvaleur de la case %d\n",i+1) ;
    scanf ("%d",&x) ; T[i]=x ;
    printf ("\nT[%d] = %d\n",i+1,T[i]) ;
  }
}


  int main (int argc , char *argv[])
    {
      remp() ;
      return 0 ;
    }