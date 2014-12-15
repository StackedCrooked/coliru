#include <stdio.h>
int main ()
{
	int n;
	printf("inserisci il numero: ");
	scanf ("%d",&n);
	int i=0;
	while (i<n)
	{
		i=i+1;
		printf ("Il risultato è: %d",i);
	}
	return 0;
}

