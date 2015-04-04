#include <stdio.h>
int main(void)
{
    float d;
    sscanf("1.2P", "%FP", &d);
    printf("d = %f\n", d);
}
