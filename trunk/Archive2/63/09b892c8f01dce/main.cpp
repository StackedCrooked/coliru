#include <stdio.h>
int main()
{
    float f = 1.0f;
    int i = *(int*)&f;
    printf("0x%08x\n", i);
}