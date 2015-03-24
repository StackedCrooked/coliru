fac(a){return(a?a*fac(a-!!a):!a);}
 
#include <stdio.h>

int main()
{
    printf("%d", fac(5));
}