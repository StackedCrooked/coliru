# include <stdio.h>

main()
{
    float notas,suma=0,promedio;
	int a,b=1;
	
	printf("Cuantos notas desea ingresar: ");
	scanf("%d", &a);
	
	while(b<=a)
	{
		printf("Ingrese la nota: ");
		scanf("%f", &notas);
		suma=suma+notas;
		b=b+1;
	}
		promedio=suma/a;
		printf("\nEl promedio es: %f\n\n",promedio);
}