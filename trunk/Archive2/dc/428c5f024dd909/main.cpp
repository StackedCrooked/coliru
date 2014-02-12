#include <iostream>


int main()
{
    double zaehler = -20;
    double teiler = 0.08;
    printf("ergebnis = %d \n", ((int) (zaehler/teiler)) << 7 );
    printf("ergebnis = %d \n", (int) (-20/0.08) << 7 );
    return 0;
}