#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

//........................................................Functia Verify_malloc..................................................
void verify_malloc (void * p, char *c)
{
    if(p == NULL){
		printf("\n Alocarea dinamica pentru pointerul %s esuata !\n",c);
	}
	else 
	{
		printf("\n Alocarea dinamica pentru pointerul %s a avut succes !",c);
		printf("\n S-a alocat memorie incepand cu adresa %d.",p);	
	}
}

void CitireVector(int *vect ,int n,char *c)
{
	vect = (int*)malloc(n*sizeof(int));//Alocam memorie vectorului  de tip int.Mem = n*4 Bytes;
	verify_malloc(vect,c);

	int i;//initializam un contor;
	printf("\n Introduceti valorile vectorului %s:\n",c);
		for(i=0 ; i<n ; i++)//Vom putea da valori de la 0 la n-1.La adresa n vom putea pune valori.In caz contrar vom avea eroare
			{
			printf("\n%s[%d]=",c,i);
			scanf("%d",&vect[i]);
			}
}
//........................................................Functia AfisareVector..................................................
void AfisareVector (int *vect,int n,char *c)
		{
			int i;
			printf("\n Vectorul %s este:",c);
				for(i=0;i<n;i++)
				{
					if(i%5 == 0)
						printf("\n");
		                printf("\t%d",vect[i]);
				}
printf("\n");
} 
int main()
{
int *v1,*v2,n;
v1 = NULL;
v2 = NULL;
int *pn;
pn = &n;

printf("\n Introduceti numarul de elemente ale vectorului:");
if(scanf("%d",&n)!=1 || n>=100 || n<=0)
{
	printf("\n Datele introduse sunt eronate sau au deoasit limita maxima");
	exit(0);
}
CitireVector(v1,n,"V1");
AfisareVector(v1,n,"V1");
//SumaElemente(v1,n,"V1");
//ProdusElemente(v1,n,"V1");
//MaxElem(v1,n,"V1");
//MinElem(v1,n,"V1");
//OrdCrescator(v1,n,"V1");
//OrdDescrescator(v1,n,"V1");
//SumVect(v1,v2,3,"V1","V2");
//ProdVect(v1,v2,3,"V1","V2");
//VectorSuma(v1,v2,3,"V1","V2");
//VectorProdus(v1,v2,3,"V1","V2");
//ProdScalar(v1,v2,2,"V1","V2");

getch();
}
