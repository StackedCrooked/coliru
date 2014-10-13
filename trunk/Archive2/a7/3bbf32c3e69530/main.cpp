#include <iostream>
#include<stdlib.h>
#include<conio.h>

using namespace std;

int main() 
{
    int mass[100][100],i,j,n,m;
    do
	{
		printf("vvedite chislo strok ne bolee 100 n: \n");
		scanf("%d",&n);
		printf("Vvedite chislo stolbzov ne bolee 100 m: \n");
		scanf("%d",&m);
	}while(n==0 || m==0);
	for (i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			printf("vvedi elementy massiva,\n");
			scanf("%d", &mass[i][j]);
		}
	}
	for (i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			printf("vash massiv");
			printf("%d", &mass[i][j]);
		}
	}
	getch();
	return 0;
}