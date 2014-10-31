#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main()
{
    srand(time(0));
    int j;
    double A, B, C, D, E, F, G, H;
    //long double A, B, C, D, E, F, G, H; // a fix
    A = (double)(rand() % 100000000)/10000000.0 - 5.0;
    B = (double)(rand() % 100000000)/10000000.0 - 5.0;
    C = (double)(rand() % 100000000)/10000000.0 - 5.0;
    D = (double)(rand() % 100000000)/10000000.0 - 5.0;
    #ifdef TINY
      A *= 1.0E-300;
      B *= 1.0E-300;
      C *= 1.0E-300;
      D *= 1.0E-300;
    #endif
    for(j=0; j<=10000000; j++)
    {
     A *= 0.9999;
     B *= 0.9999;
     C *= 0.9999;
     D *= 0.9999;
     E = A * B + C - D; // some exercise code
     F = A - C * B + D;
     G = A + B + C + D;
     H = A * C - B + G;
     E = A * B + C - D;
     F = A - C * B + D;
     G = A + B + C + D;
     H = A * C - B + G;
     E = A * B + C - D;
     F = A - C * B + D;
     G = A + B + C + D;
     H = A * C - B + G;
    }
    printf("%f", E);
    printf("%f", F);
    printf("%f", G);
    printf("%f", H);
    return 0;
}