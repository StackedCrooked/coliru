#include <stdio.h>
#include <stdlib.h>

int main (){
    int X;
    float Y,KM;
    
    scanf ("%i",&X);
    scanf ("%f",&Y);
    
    KM = X/Y;
    
    printf ("%f  km/l",KM);
    
    return 0;   
}