#include <stdio.h>
#include <stdlib.h>

int main()
{
    int A, B, C, Br, Nu, res;

    printf ("Digite a quantidade de votos do politico A, B e C respectivamente: \n");
	scanf ("%d %d %d", &A, &B, &C);
	printf ("Digite a quantidade de votos em Branco e Nulos respectivamente: \n");
	scanf ("%d %d", &Br, &Nu);

    res = A + B + C;

	printf ("A quantidade de votos validos e: %d \n", res);

	A = A*100 / (res + Br + Nu);
	printf ("A quantidade de percentual de votos no politico A e: %d \n", A);


    B = B*100 / (res + Br + Nu);
	printf ("A quantidade de percentual de votos no politico B e: %d \n", B);

	C = C*100 / (res + Br + Nu);
	printf ("A quantidade de percentual de votos no politico C e: %d \n", C);

	Br= Br*100 / (res + Br + Nu);
	printf ("A quantidade de percentual de votos em branco e: %d \n", Br);

    Nu = Nu*100 / (res + Br + Nu);
	printf ("A quantidade de percentual de votos nulos e: %d \n", Nu);



	if (A>50) {
        printf ("Politico A e o vencedor, nao e necessario segundo turno \n");
	}
	else if (B>50) {
        printf ("Politico B e o vencedor, nao e necessario segundo turno \n");
	}
	else if (C>50) {
        printf ("Politico C e o vencedor, nao e necessario segundo turno \n");
	}

	if (A<50 && A>B && A>C){
        printf ("Politico A fica em primeiro lugar, disputa segundo turno ");
	}
    else if (B<50 && B>A && B>C){
        printf ("Politico B fica em primeiro lugar, disputa segundo turno ");
    }
	else if (C<50 && C>B && C>A){
        printf ("Politico C fica em primeiro lugar, disputa segundo turno ");
	}


	if (A<B && A>C){
       printf ("com A \n");
	}
    if (B<C && B>A){
       printf ("com B \n");
	}
	if (C<B && C>A){
       printf ("com C \n");
	}



	system ("PAUSE");

    return 0;
}
