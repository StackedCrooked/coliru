#include <iostream>
#include <math.h>


int main()
{
    int first = 2;
    int inc =20;
    int last = 1105;
    
    while(first<=last)
    {
        int n =(int)log10(last)-(int)log10(first);
        while(n>0){
            printf("0");
            n--;
        }
        printf("%d\n",first);
        first+=inc;
    }
}
