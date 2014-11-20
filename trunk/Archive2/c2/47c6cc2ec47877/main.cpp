#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
struct Mot{
    char mot[100];
    char* somme;
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

int myAtoi(const char* str)
{
    int resultat = 0;
    int i=0;
    while(str[i]!='\0')
    {
        resultat += ConvertCharsToInt(str[i]);
        i++;
    }
    return resultat;
}

char* SumCharsAndDigits(const char* str)
{
    int resultat = myAtoi(str);
    int tailleRes = SizeStringFromInt(resultat);
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
     else
        precedent=1;
     i++;
    }
    if(precedent ==1)
        return compteur+1;
    else
        return compteur;
}

int partition( struct Mot* tab, int debut, int fin)
{
    int pivot = myAtoi(tab[debut].somme);

    int tokenDebut=debut;
    int tokenFin=fin+1;
    struct Mot temp;
    while(1)
    {
        do{
            tokenDebut++;}
        while(myAtoi(tab[tokenDebut].somme)<=pivot && tokenDebut < fin);

        do
            tokenFin--;
        while(myAtoi(tab[tokenFin].somme)>pivot);

        if(tokenDebut >= tokenFin)
            break;



        temp = tab[tokenDebut];
        tab[tokenDebut] = tab[tokenFin];
        tab[tokenFin] = temp;
    }

    temp = tab[debut];
    tab[debut] = tab[tokenFin];
    tab[tokenFin] = temp;
    return tokenFin;
}

void Quicksort(struct Mot* tab, int debut, int fin)
{
    int position;

    if(debut-fin>=0) return;

    position = partition(tab,debut,fin);
    Quicksort(tab,debut,position-1);
    Quicksort(tab,position+1,fin);

}


void PrintWordsSorted(const char* str)
{
    int i=0;
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
                memcpy(tableau[numero].mot,&str[debutMot],i-debutMot);
                tableau[numero].mot[i-debutMot]='\0';
                tableau[numero].somme = SumCharsAndDigits(tableau[numero].mot);
                numero++;
            }
            debutMot=i+1;
        }
        i++;
    }

    if(str[i-1]!=' ')
    {
        memcpy(tableau[numero].mot,&str[debutMot],i-debutMot);
        tableau[numero].mot[i-debutMot]='\0';
        tableau[numero].somme = SumCharsAndDigits(tableau[numero].mot);
    }

    Quicksort(tableau,0,nombreMot-1);
    for(i=0;i<nombreMot;i++)
    {
        printf("%s:%s\n",tableau[i].somme,tableau[i].mot);
    }

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

void testPrintWordsSorted()
{
    printf("\nTEST DE PrintWordsSorted\n\n");
    printf("\nPhrase : Mon code est cool mais en retard \n\n");
    PrintWordsSorted("Mon code est cool mais en retard");
    printf("--------------------------------");
}

int main()
{
    testSumCharsAndDigits();
    testPrintWordsSorted();
    return 0;
}
