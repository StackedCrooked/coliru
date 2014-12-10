#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 256

int nbChar(const char* str);
char* SumCharsAndDigits(const char* str);
void PrintWordsSorted (const char* str);

int main()
{
    char* Somme;
	const char* str;
	str = (const char*)malloc(sizeof(const char)*MAX_LENGTH);
	
	while(1)
	{
		printf("Entrée:");
		scanf("%s",str);
		Somme = SumCharsAndDigits(str);
		printf("=> Sortie : %c\n", Somme[0]);
	}

	PrintWordsSorted(str);

	system("PAUSE");
	return 0;
}

char* SumCharsAndDigits(const char* str)
{
	int i;
	int n = nbChar(str);
	int Som=0;
	char Somme[MAX_LENGTH] = {0};

	for(i=0;i<n;i++)
	{
		Somme[i] = str[i];
	}

	do
	{
		Som=0;
		for(i=n-1;i>=0;i--)
		{
			if(Somme[i]<=90 && Somme[i]>=65)
				Som+=Somme[i]-64;
			else if(Somme[i]<=122 && Somme[i]>=97)
				Som+=Somme[i]-96;
			else if(Somme[i]<=57 && Somme[i]>=48)
				Som+=Somme[i]-48;
		}
		Somme[0] = Som;
		i=0;
		while(1)
		{
			Somme[i+1] = Somme[i]/10;
			Somme[i] = Somme[i] - Somme[i+1]*10 + 48;
			if(Somme[i+1] == 0) 
				break;
			i++;
		}
		n= nbChar(Somme);
		
	}while(Som>9);

	return Somme;
}

void PrintWordsSorted (const char* str)
{
	int i=0,j=0,k=0;
	int Tab_Valeur[10];
	char *var;
	int n= nbChar(str);
	char Tab[MAX_LENGTH][MAX_LENGTH] = {'\0'};

	int min, indice_min;

	str = "chat test huile";

	while(str[j] != '\0')
	{
		while(str[j] != ' ' && str[j] != '\0')
		{
			Tab[i][k] = str[j];
			j++;k++;
		}
		if(str[j] == '\0') break;
		j++;i++;k=0;
	}
	i=i+1;
	for(k=0; k<i; k++)
	{
		var = SumCharsAndDigits(Tab[k]);
		Tab_Valeur[k] = var[0]-48;
	}
	j=i;
	while(j>0)
	{
		min = Tab_Valeur[0];
		indice_min = 0;
		for(k=1; k<i; k++)
		{
			if(Tab_Valeur[k] < min && Tab_Valeur[k]!=0)
			{
				min = Tab_Valeur[k];
				indice_min = k;
			}
		}
		printf("%d : %s\n", min, Tab[indice_min]);
		Tab_Valeur[indice_min] = 0;
		j--;
	}


}

int nbChar(const char* str)
{
	int n=0;

	while(str[n]!='\0')
		n++;
	return n;
}


