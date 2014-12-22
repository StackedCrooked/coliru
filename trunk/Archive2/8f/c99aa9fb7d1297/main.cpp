#include <stdio.h>
#include <stdlib.h>

// Attention la fonction retourne -1 en cas d erreur
int longeur(const char* str)
{
    int i = 0;
	
	if (str == NULL)
	{
		return -1;
	}
		
	while (str[i])
	{
		i++;
	}
	return i;
}

// En cas d erreur la fonction retourne NULL
char* SumCharsAndDigits(const char* str)
{
	int i = 0;
	int somme = 0;
	int l = longeur(str);
	
	if (l == -1)
	{
		return NULL;
	}

	for (i = 0; i < l; i++)
	{
		if (str[i] >= 'a' && str[i] <= 'z')
		{
			somme += str[i] - 'a' + 1;
		}

		else if (str[i] >= 'A' && str[i] <= 'Z')
		{
			somme += str[i] - 'A' + 1;
		}

		else if (str[i] >= '1' && str[i] <= '9')
		{
			somme += str[i] - '1' + 1;
		}	
	}
	
	if (somme >= 0 && somme <= 9)
	{
		char* res = (char*) malloc(2);
		char x = somme  + '0';
		res[0] = x;
		res[1] = 0;
		return res;
	}
	
	int nb_div = 1;
	l = 0;
	while (somme / nb_div >= 1)
	{
		nb_div = nb_div * 10;
		l++;
	}
		
	char* res = (char*)malloc(l+1);
	for (i = 0; i < l; i++)
	{
		char x = somme / (nb_div/10) + '0';
		somme -= (somme / (nb_div / 10)) * (nb_div / 10);
		nb_div = nb_div / 10;
		res[i] = x;
	}
	res[l] = 0;
	
	return SumCharsAndDigits(res);
}

// trier tableau de mots
void trier_tableau_mot(char** tab_mots, int taille)
{
	int verif = 1;
	int i = 0;
	do
	{
		verif = 1;
		for (i = 0; i < taille-1; i++)
		{
			char* s1 = SumCharsAndDigits(tab_mots[i]);
			char* s2 = SumCharsAndDigits(tab_mots[i + 1]);
			if (s2[0] < s1[0])
			{
				verif = 0;
				char* temp = tab_mots[i+1];
				tab_mots[i + 1] = tab_mots[i];
				tab_mots[i] = temp;
			}
			free(s1);
			free(s2);
		}
	} while (verif == 0);
}

// Remplissage du tableau de mots
char** extraire_mot(char const* str, int* taille)
{

	int i = 0;
	int j = 0;
	int m = 0; // L'indice de debut d'un mot
	int l = longeur(str);
	int idx = 0;

	if (l == -1)
	{
		return NULL;
	}

	char** tab_mots = (char**)malloc(l * sizeof(char*)); // Allocation d'un tableau de mots

	for (i = 0; i < l + 1; i++)
	{
		char* mot = { 0 };
		if (str[i] == ' ' || str[i] == 0)
		{
			mot = (char*)malloc(i - m + 1);
			int k = 0;
			for (j = m; j < i; j++)
			{
				mot[k] = str[j];
				k++;
			}
			mot[k] = 0;
			m = i;

			while (str[m] == ' ')
			{
				m++;
				i++;
			}

			tab_mots[idx] = mot;
			idx++;
		}
	}
	*taille = idx;
	return tab_mots;
}

// Affichage de valeurSumDigit : MOT
void afficher_tableau_mot(char** tab_mots, int taille)
{
	int i = 0;
	for (i = 0; i < taille; i++)
	{
		char* s = SumCharsAndDigits(tab_mots[i]);
		printf("%s : %s\n", s, tab_mots[i]);
		free(s);
	}
}

void PrintWordsSorted(const char* str)
{
	int taille = 0;
	int i = 0;
	char** tab = extraire_mot("mon code est cool !", &taille);
	trier_tableau_mot(tab, taille);
	afficher_tableau_mot(tab, taille);
	for (i = 0; i < taille; i++)
	{
		free(tab[i]);
	}
}

int main()
{
	int i = 0;
	char const* c[4] = { "123", "1d3", "1D3", "5#83" };
	for (i = 0; i < 4; i++)
	{
		char* p = SumCharsAndDigits(c[i]);
		printf("Entree %s ==> Resultat %s\n", c[i],p);
		free(p);
	}
	
	PrintWordsSorted("mon code est cool !");

	return 0;
}
