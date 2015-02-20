#include <iostream>
#include <string>
#include <vector>
#include <string.h>
#include <stdio.h>

int main()
{
   char str[80] = "imparare a programmare richiede pratica" ;
   char s[2] = " " ; // stringa del separatore
   char *parola;
   parola = strtok(str, s)
   while (parola !=0) {
        printf ( " %s\n", parola) ;
        parola = strtok (0, s);
   }
}
