#include <stdio.h>
#include <stdlib.h>

int main()
{
    int x = 0xBAADC0DE;
    char* c_ptr = (char*)&x;
    
    for (int i = 0; i < 3; ++i, ++c_ptr)
    {
        printf("%x\n", (*c_ptr) & 0xFF);
    }
    
    return EXIT_SUCCESS;
}
