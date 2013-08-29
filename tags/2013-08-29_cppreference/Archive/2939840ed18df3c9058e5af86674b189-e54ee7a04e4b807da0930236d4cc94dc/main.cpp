#include <stdio.h>
#include <stdlib.h>
int triple(int nombre)
{
    int resultat=0;
    resultat=nombre*3;
    return resultat;
}
int main()
{
    int nbraa=0;
    int result=0;
    printf("saisissez un nombre et je vous donne le triple");
    scanf("%d", &nbraa);
   result= triple(nbraa);
   return result;
    
    
}