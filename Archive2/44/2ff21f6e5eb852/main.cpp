#include <stdio.h>

int main(void)
{
    float top[2] = {0.0, 66.0};
    printf("%f %f \n", *top, *(top+1));
    printf("%f %f \n", top[0], top[1]);
    return 0;
}
