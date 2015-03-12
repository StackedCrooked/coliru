#include <stdio.h>

int main()
{
    char *st1 = "hello";
    char *st2 = "hello";
    
    if (st1 == st2)
        printf("equal");
    else
        printf("unequal");
        
    return 0;
}