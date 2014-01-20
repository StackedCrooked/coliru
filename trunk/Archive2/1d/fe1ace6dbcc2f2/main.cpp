#include <stdio.h>
#include <stdlib.h>

typedef union
{
    double f;
    unsigned long long u;
    int long long i;
} r;

int main()
{
    r var1, var2;
    
    //var1.f = 0 ;
    //var2.f = 0 ;
    
    var1.f = -3.5;
    var2.u = 3;
    
    var1.f = var1.f + var2.u;
    
    printf( "%zu %zu %zu\n", sizeof(double), sizeof(unsigned long long), sizeof(int long long) );
    printf("%f", var1.f);
    return 0;
}
