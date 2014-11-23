#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char most_recurrent_char(char *buf)
{
    char* tabChar; // tableau de stockage unique des caractères
	int* tabOccur; // tableau de leurs occurences dans le texte
	char tmp;
	char mostOccur='_';
	int maxOccur=0, j=0;
	int n, i;
	
	n= (strlen(buf)<26) ? strlen(buf) : 26; // on ne s'intéresse ici qu'à des lettres de l'alphabet latin, casse ignorée.
	if(n!=0)
	{
		tabChar=(char*)malloc(n*sizeof(char));
		tabOccur=(int*)malloc(n*sizeof(int));
		
		for(i=0; i<n; i++)
		{
			tabChar[i]='_';
			tabOccur[i]=0;
		}
		while ((*buf)!='\0')
		{
			if( ((*buf)>=65 && (*buf)<=90) || ((*buf)>=97 && (*buf)<=122) )
			{
				if ((*buf)>=65 && (*buf)<=90) // passage en minuscule
					tmp=(*buf)+32;
				else
					tmp=(*buf);
				while (tabChar[j]!=tmp && tabChar[j]!='_')
				{
					j++;
				}
				(tabOccur[j])++;
				if(tabChar[j]=='_')
					tabChar[j]=tmp;
				j=0;
			}	
			*(buf++);
		}
		
		for(i=0; i<n; i++)
		{
			if(tabOccur[i]>maxOccur)
			{	
				mostOccur=tabChar[i];;
				maxOccur=tabOccur[i];
			}
		}
		free(tabChar);
		free(tabOccur);
	}
	return mostOccur;
}

int main(void)
{
	char c;
	char* buf=(char*)"Everyone tells the most recurrent character in this sentence is e";

	c=most_recurrent_char(buf);
	if (c=='_')
		printf("Votre phrase est vide, ou bien ne contient pas de caractère autorisé. \n");
	else
		printf("Le caractère le plus récurrent est \"%c\". \n",c);
	return 0;
}