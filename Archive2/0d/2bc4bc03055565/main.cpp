#include <stdio.h>
#include <math.h>

int main() {
    
    int celsius;
    double kelvin;
    double farenthai;
    
    printf ("Introduza valor a convertir: ");
    scanf ("celsius %0.2lf", celsius );
    
    kelvin=celsius+273;
    farenthai=1.8*celsius+32;
    
    printf("kelvin %0.2lf", kelvin);
    printf("farenthai %0.2lf", farenthai);
    
    return 0;



}