#include <stdio.h>
#define FACT 7


int f = FACT;
int fac = 1;

int main()
{
    if (f == 0){
        printf("%d!=%d\n", FACT, fac);
        return 0;
    }
    else{
        fac*=f ;
        --f;
        main();
    }    
    return 0;
}
