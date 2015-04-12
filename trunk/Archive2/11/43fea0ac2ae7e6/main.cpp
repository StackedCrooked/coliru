#include <stdio.h>
#include <stdlib.h>

int main()
{
    int x = 0xBAADC0DE;

    int* ptr_x = &x;
    
    *ptr_x = 0xAAAA;
    
    printf("%X\n", x);
    
    return EXIT_SUCCESS;
}
