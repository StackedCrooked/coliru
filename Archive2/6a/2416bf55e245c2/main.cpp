#include <stdio.h>

int mult (int a,int b) {


     int i;
	 int summe = 0;

	 for (i =1; i <= a; i++)

	 {
			summe = summe + b;

	 }



	return summe;

}

int main (){

	setbuf(stdout, NULL);

	int a;
	int b;

	printf("Geben Sie eine Zahl a ein : \n");
	scanf("%d", &a);

	printf("Geben Sie eine Zahl b ein : \n");
	scanf("%d", &b);

	printf("Das Ergebnis ab von Multiplikation ohne . ist : %d\n",  mult(a,b));


	return 0;

}
