#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>


void kelimearama(int a);
char menu();
void txtdoldur();
void listeleme();
void tarama();
void ekleme();
void silme();

int main()
{
    txtdoldur();
	while (1)
	{
		char sec = menu();
		switch (sec)
		{
		case '1': kelimearama(0); break;
		case '2': kelimearama(1); break;
		case '3':  break;
		case '4': listeleme(); break;
		case '5': ekleme(); break;
		case '6': silme(); break;
		case '9': exit(0); break;
		default: menu(); break;
		}
		system("CLS");
	}
	system("PAUSE");
	return 0;
}

void txtdoldur()
{

	FILE  *soku, *tyaz, *iyaz;
	char  turkce[100][100], ingilizce[100][100], tgecici[100], igecici[100], sozluk[100][100][100];
	int   sayac = 0, k, l, m, n, si, sj;
	int asd;


	soku = fopen("sozluk.txt", "r");

	if (soku == NULL)
	{
		printf("Sozluk dosyasi acilamiyor...");
	}
	// sozluk dosyasini okuyo

	while (!feof(soku))
	{
		fscanf(soku, "%s %s", &turkce[sayac], &ingilizce[sayac]);
		sayac++;
	}
	fclose(soku);

	/*       for(k=0;k<sayac;k++)
	{
	printf("%d %s \t %s \n",k+1,&turkce[k],&ingilizce[k]);
	}
	*/     /// turkce alfabetik siralama

	for (si = 0; si<sayac; si++)
		for (sj = si + 1; sj<sayac; sj++)
			if (strcmp(turkce[si], turkce[sj])>0)
			{
		strcpy(tgecici, turkce[sj]);
		strcpy(turkce[sj], turkce[si]);
		strcpy(turkce[si], tgecici);

		strcpy(igecici, ingilizce[sj]);
		strcpy(ingilizce[sj], ingilizce[si]);
		strcpy(ingilizce[si], igecici);
			}
}