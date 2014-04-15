#include <stdio.h>
#include <ctype.h>
#include <limits.h>
 
int main(void)
{
    for (int ndx=0; ndx<=UCHAR_MAX; ndx++)
        if (isalpha(ndx)) printf("%c", ndx);
    printf("\n");
 
    return 0;
}