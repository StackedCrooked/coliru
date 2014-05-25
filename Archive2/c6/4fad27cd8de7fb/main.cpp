#include<iostream>
#include <malloc.h>
#include <stdlib.h>
using namespace std;

char* vvod_str()
{
    char* str = (char*)malloc(sizeof(char));
	int j = 1;
	do{
		str = (char*)realloc(str, (j)*sizeof(char));
		str[j - 1] = getchar();
		j++;
	} while (str[j - 2] != '\n');
	str[j - 2] = 0;
	return str;
}

int main()
{
	int n,i;
	char razd,slovo;
	printf("vvedite kol ctrok: \n");
	scanf("%d",n);
	printf("vvedite stroky razdelitelei: \n");
	scanf("%c", razd);
	printf("vvedite slovo: \n");
	scanf("%c", slovo);
	char** str = (char**)malloc((n)*sizeof(char*));
	for (i = 0; i < n; i++)
	str[i] = (char*)malloc(sizeof(char));
	printf("Vvedite Text: \n");
	for (i = 0; i < n; i++)
	{
		str[i] = vvod_str();
	}

}