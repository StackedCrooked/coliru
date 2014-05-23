/*sconto di un prodotto*/
#include<stdio.h>
#include<stlib.h>
int main()
{
    int p, s, t;
    printf("inserisci valore di p:n\");
    scanf("%d",&p);
    s = p*3/100;
    t = p - s;
    printf("il prezzo scontato e' :" "%d \ n",t);
    system("pause");
    return 0;
}
    