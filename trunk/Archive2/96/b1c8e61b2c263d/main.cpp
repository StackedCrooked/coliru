#include <stdio.h>
#include <stdlib.h>

void tri_rapide(int* tab, unsigned int in_start, unsigned int in_end)
{

  if(in_start == in_end) return;

  unsigned int k=0;
  //Choix du pivot
  int pivot = *(tab+in_start); //Arbitraire, premier élément
  *(tab+in_start) = *(tab+in_end);
  *(tab+in_end) = pivot;

  //Placer les éléments supérieurs au pivot en début de tableau, et les éléments inférieurs après
  unsigned int i=in_start;
  unsigned int j=in_start;
  int temp=0;

  for(i=in_start;i<in_end;i++)
    {
      if(*(tab+i)<=pivot)
        {
	        temp = *(tab+j);
	        *(tab+j) = *(tab+i);
	        *(tab+i) = temp;
	        j++;
	    }
    }
  temp = *(tab+in_end);//On remet le pivot à la suite des derniers éléments déplacés
  *(tab+in_end) = *(tab+j);
  *(tab+j) = temp;

  //Appel du tri rapide sur les deux sous tableaux, sauf si les éléments sont déjà ordonnés
  if(j>in_start) tri_rapide(tab, in_start, j-1);
  if(j<in_end) tri_rapide(tab, j+1, in_end);

}

int main()
{
  int tab[20] = {645,64,8,16,466,4,964,68,64,9,987,48,98,341,5,1,648,64,31,6};
  
  unsigned int k=0;
  printf("Tableau à trier :");
  for(k=0; k<20; k++)
    {
      printf("%d ", tab[k]);
    }
  printf("\n");

  tri_rapide(&tab, 0, 19);

  printf("Tableau trié :");
  for(k=0; k<20; k++)
    {
      printf("%d ", tab[k]);
    }
  printf("\n");

  return 0; 
}
