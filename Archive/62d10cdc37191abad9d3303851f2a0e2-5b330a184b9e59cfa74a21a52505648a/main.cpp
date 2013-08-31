#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    double x = (double)rand() / RAND_MAX;
    
    printf("%f\n", x * x * x);
    printf("%f\n", pow(x, 3.0));
}
