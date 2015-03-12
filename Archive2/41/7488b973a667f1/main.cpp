#include <stdio.h>
#include <stdlib.h>

int main(int agrc, char* argv[])
{
    int num = atof(argv[1]);

    *par_ou_impar(num);

    return 0;
}

char *par_ou_impar(int aux)
{
    return (aux % 2 == 0) ? "par" : "impar";
}