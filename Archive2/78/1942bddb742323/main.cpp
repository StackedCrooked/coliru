#include <stdio.h>
 
int main(void)
{
    printf("sizeof(_Bool) = %zu\n", sizeof(_Bool));
 
    _Bool b;
    b = 2;
    printf("b  = %d\n", b);    // 2 or 1?
    printf("!b = %d\n", !b);   // 0
 
    b = 0;
    printf("!b = %d\n", !b);   // 1
 
    if (b) printf("true\n");   // false
    else   printf("false\n");
 
    return 0;
}