#include <stdio.h>

static double seed; // uma seed entre 0 e 1
double random() {
   seed /= 1125899839733759;  // um número primo
   seed *= 18014398241046527; // outro
   seed -= (int)seed;         // normalizar
   return seed;
}

int main() {
    seed = 0.753;
    printf("%f\n", random());
    printf("%f\n", random());
    printf("%f\n", random());
    printf("%f\n", random());
    printf("%f\n", random());
}