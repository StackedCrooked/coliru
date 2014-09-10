#include <stdio.h>
int main () {
    int n1,n2;
	printf ("Este eh um programa que faz com que o primeiro numero digitado seja divisivel por zero\n");
	printf ("Digite o primeiro numero\n");
	scanf ("%d",&n1);
	printf ("Digite o segundo numero\n");
	scanf ("%d",&n2);
	if (n1%n2==0) {
		printf ("A operação é divisivel\n");
	} else {
		printf ("A operação não é divisível\n");
	}
	return 0;
}

