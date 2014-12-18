#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct mot
{
    char *somme;
    char *word;

}mot;


int Traitement(int a)
{
    int somme=0;
    int sommeFinal =0;
    int s =0;
    int mod =0;

    s=a;
    sommeFinal=a;
    while(sommeFinal>9)
    {
       somme =0;
       s=sommeFinal;
       while(s>9)
       {
           mod = s%10;
           s = s/10;
           somme +=mod;
      }
       somme += s%10;
       sommeFinal = somme;
    }

    return sommeFinal;
}

char* SumCharsAndDigits(const char* str)
{
    int i=0;
    char a='a';
    char A = 'A';
    int somme =0;

    char *s=NULL;
    s = (char*)malloc(sizeof(char) * 1);
    if(!s)
        return NULL;

    while(str[i]!='\0')
    {
        if(str[i] >= a && str[i] <='z')
        {
            somme += (str[i] -a +1);
        }
        else if(str[i]>= A && str[i] <= 'Z')
        {
            somme +=  (str[i] - A +1);
        }
        else if(str[i]>= '0' && str[i] <='9')
        {
            somme +=  str[i] - '0';
        }
        else
        {
            somme += 0;
        }
        i++;
    }

    somme = Traitement(somme);
    *s = '0' + (char)somme;

     return s;
}


int strlen(const char* str)
{
    int i=0;

    while(str[i]!=NULL)
    {
        i++;
    }

    return i;
}

void PrintWordsSorted(const char* str)
{


}



mot *cptMot(const char* str, mot *tabMot)
{
    int cpt=0;
    int j=0;
    int i=0;
    int k=0;
    int l=0;

    while(str[i]!=NULL)
    {
        j=0;
        while(str[i]!=' ' && str[i]!=NULL)
        {
           i++;
           j++;
        }

        if(str[i]!=' ')
            cpt++;

        i++;
    }

    tabMot = (mot*)malloc(sizeof(mot) * cpt);
    if(!tabMot)
        return NULL;

    i=0;
    j=0;
    k=0;
    l=0;
    while(str[i]!=NULL)
    {
        j=0;
        while(str[i]!=' ' && str[i]!=NULL)
        {
           i++;
           j++;
        }

        if(j!=0)
        {
            tabMot[l].word =(char*)malloc(sizeof(char) * (j+1));
            if(tabMot[l].word)


            for(k=0;k<j;k++)
            {
                tabMot[l].word[k]=str[i-j+k];
            }
             tabMot[l].word[j]='\0';

            tabMot[l].somme =SumCharsAndDigits(tabMot[l].word);
            printf("\n mot = %s  %c",tabMot[l].word,*tabMot[l].somme);
        }

        l++;
        i++;
    }

    return tabMot;
}

void lecture(mot *tab)
{
    if(!tab)
        return;

    int i=0;
    for(i=0;i<4;i++)
    {
        printf("\n %s",tab[i].word);
    }

}


int main()
{
    const char str[] ="12HelloWOrld!)A  erzerz dsf fdfg";

    mot *tabMot = NULL;

    tabMot=cptMot(str,tabMot);

    if(!tabMot)
        printf("errerur\n");


    const char str2[] ="12HelloWOrld!)A";
    char *result =SumCharsAndDigits(str2);
    printf("\n\nresult = %c\n",*result);

     if(!tabMot)
        free(tabMot);

    return 0;
}
