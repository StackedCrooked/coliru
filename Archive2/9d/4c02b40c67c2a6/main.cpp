#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char* SumCharsAndDigits(const char* str);

//fonction renvoyant la longueur d'une chaine de caractere
int stringLength(const char* str);

// fonction renoyant la place d'une lettre (numéro) dans l'alphabet
int letterID(char c);

int main(int argc, char** argv)
{
    const char* test = "5#83"; //tentative d'ajout du symbôle de fin de chaîne de caractère
    printf("Sortie : %d \n", SumCharsAndDigits(test) - '0');
    return 0;
}

int stringLength(const char* str)
{
	int nb = 0;
	char c = 0;
	do
	{
		c = str[nb]; //l'erreur de segmentation se produit ici car la condition d'arrêt de la boucle ne reconnait pas le symbole de fin de chaine de caractères
		++nb;
	}while(c != '\0'); //c'est cette condition qui pause problème
	return --nb;
}

int letterID(char c)
{
	char tabUpper[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char tabLower[27] = "abcdefghijklmnopqrstuvwxyz";
	int i = 0;
	int value = 0;
	for(i=0; i<26; ++i)
	{
		if(c == tabUpper[i] || c == tabLower[i]) //si ce n'est pas une lettre value = 0
			value = i;
	}
	if (value > 0) ++value;
	return value;
}

char* SumCharsAndDigits(const char* str)
{
	int total = 0;
	int i = 0;

	//if(str != NULL) // on vérifie que la chaine est initialisée
	//{
		int length = stringLength(str);
		for(i=0; i<length; ++i)
		{
			if(isdigit(str[i])) //si le caractere est un chiffre
				total += str[i] - '0';
			else 
				total += letterID(str[i]);
		}

		if (total >= 10)
		{
			int res = total % 10; // reste
			int deca = (total - res) / 10; // dizaine
			total = res + deca;
		}

	//}
	return (char)total + '0';
}