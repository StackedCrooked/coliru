#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
    
    double a = rand();
    double b = rand();
    
    double c = exp(2.0*a) * exp(3.0*b);
    
    printf("%f\n", c);
    
    return 0;
}
