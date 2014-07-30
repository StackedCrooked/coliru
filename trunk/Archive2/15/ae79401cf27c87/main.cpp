#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int a, b, c;
    a = atoi(argv[1]);
    b = 4;
    c = a / (b * b);
    
    printf("%d", c);

    return 0;
 }

