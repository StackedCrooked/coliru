#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
struct Mot{
    char* mot;
    int somme;
};

int ConvertCharsToInt(const char c)
{
    int ascii = (int)c;

    if(ascii>=48 && ascii<=57)
        return ascii-48;
    else if(ascii>=97 && ascii<=122)
        return ascii-96;
    else if(ascii>=65 && ascii<=90)
        return ascii-64;
    else
        return 0;

}

int SizeStringFromInt(const int i)
{
    int taille = 0;
    int q = i;
    while(q != 0 )
    {
        q /= 10;
        taille ++;
    }

    return taille;
}


char* SumCharsAndDigits(const char* str)
{
    int i=0;
    int tailleRes = 1;
    int resultat = 0;

    while(str[i]!='\0')
    {
        resultat += ConvertCharsToInt(str[i]);
        i++;
    }

    tailleRes = SizeStringFromInt(resultat);
    char* resChar = (char*)malloc(sizeof(char)*tailleRes);
    sprintf(resChar,"%d",resultat);

    if(tailleRes > 1)
        resChar = SumCharsAndDigits(resChar);

    return resChar;
}

int compteMot(const char* str)
{
    int i=1;
    int compteur =0;
    int precedent;
    if(str[0]==' ')
        precedent = 1;
    else
        precedent = 0;


    while(str[i]!='\0')
    {
     if(str[i]==' ')
     {
         if(precedent!=0)
         {
            compteur++;
            precedent = 1;
         }

     }
     i++;
    }
    return compteur;
}

void PrintWordsSorted(const char* str)
{
    /*int i=0;
    int debutMot=0;

    int nombreMot = compteMot(str);
    int numero=0;
    struct Mot tableau[nombreMot];

    while(str[i]!='\0')
    {
        if(str[i]==' ')
        {
            if(debutMot!=i)
            {
                memcpy(tableau[numero].mot,&str[i],i-debutMot); // je n'ai pas réussi à implémenter la fonction pour recuperer le mot
               // tableau[numero].somme = SumCharsAndDigits(tableau[numero].mot);
            }
            debutMot=i+1;
        }
        i++;
    }*/

    /*for(i=0;i<nombreMot;i++)
    {
        printf("%d:%s\n",tableau[numero].somme,tableau[numero].mot);
    }*/

}



void testSumCharsAndDigits()
{
    printf("\nTEST DE SumCharsAndDigits\n\n");
    char* test = SumCharsAndDigits("123");
    if(strcmp(test,"6")==0)
        printf("123 = 6\n");

    test = SumCharsAndDigits("1d3");
    if(strcmp(test,"8")==0)
        printf("1d3 = 8\n");

    test = SumCharsAndDigits("1D3");
    if(strcmp(test,"8")==0)
        printf("1D3 = 8\n");

    test = SumCharsAndDigits("5#83");
    if(strcmp(test,"7")==0)
        printf("5#83 = 7\n");
    printf("--------------------------------");
}

int main()
{
    testSumCharsAndDigits();
     printf("\nTEST DE PrintWordsSorted\n\n");
    PrintWordsSorted("Mon code est cool mais pas fini");
    printf("--------------------------------");
    return 0;
}
