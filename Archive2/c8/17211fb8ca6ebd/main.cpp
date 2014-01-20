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
    
    var1.f = -3.5;
    var2.u = 3;
    var1.u = var1.u + var2.u;
    
    var2.f = -3.5;
    printf("%.17f\n", var1.f);
    printf("%.17f\n", var2.f);
    printf("%llu\n",var1.u);
    printf("%llu\n",var2.u);

    return 0;
}
