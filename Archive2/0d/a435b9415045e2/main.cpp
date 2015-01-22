// AUTORI: Dona' Chiara e Pavan Carlotta
// DATA: 19/01/2015
// TITOLO: unione di due stringhe


using namespace std;

#include <stdio.h>
#include <string.h>

int main()
{

char frase[82],*p,*s,c;
puts("Inserisci la frase (Max 80 caratteri):");
fgets(frase,82,stdin);
frase[strlen(frase)-1]='\0';
puts("Inserisci il carattere da rimuovere:");
c=getchar();
for (s=p=frase;*p=*s;p+=(*s++!=c));
printf("Risultato: %s\n",frase);
return 0;
}