#include <stdio.h>
#include <stdint.h>

int main(void)
{
    float x = 0.1;
    float y = x * x;
    
    printf("x = %f\n", x);
    printf("y = %f\n", y);

    if (y == 0.01)
    {
        printf("Success!\n");
    }
    else
    {
        printf("Failure!\n");
    }
    
    // Look at bits
    float z = 0.01;
    union
    {
        float f;
        uint32_t u;
    } un;
    
    un.f = y;
    printf("as hex, y = %x\n", un.u);
    un.f = z;
    printf("as hex, z = %x\n", un.u);
}