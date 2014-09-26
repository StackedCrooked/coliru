#include <stdio.h>
int main()
{
int annee, n1, n2, n3;
printf("Entrer une année\n");
scanf("%d",&annee);
n1=annee % 4;
n2=annee % 100;
n3=annee % 400;
if ((n1==0 && n2!=0) || n3==0) {
printf("L'année est bissextile\n");
}
else{
printf("L'année n'est pas bissextile\n");
}
return 0;
}