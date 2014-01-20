#include <stdio.h>
#include <iostream>
#include <math.h>
#include <cstdlib>
int main () {
    float a,b,c,d,e,f;
    printf ("Unesi x točke T. ");
    scanf ("%f", &a);
    printf ("Unesi y točke T. ");
    scanf ("%f", &b);
    printf ("Unesi A, B, C pravca Ax+By+C. ");
    scanf ("%f %f %f", &c, &d, &e);
    d=(abs(c+d+e))/(sqrt(a*a+b*b));
    printf ("Udaljenost od točke T do pravca iznosi %f. ",d);
    system ("pause");
    return 0;}