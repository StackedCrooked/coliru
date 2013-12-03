#include <stdio.h>
#include <string.h>
static int i=1;
f(int n)
{
    if(n>=5)
        return n;
    n=n+i;
    printf("Before - %d\n",i);
    i++;
    printf("after - %d\n",i);
}

main()
{
    int y;
    y=f(1);
    printf("Main - %d\n",y);
    return 0;
}