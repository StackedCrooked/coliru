#include <stdio.h>

int main()
{
    float a = 1.1f;
    float b = 2.2f;
    float c = 3.3f;
    
    printf("(a + b) + c = %lg\n", (a + b) + c);
    printf("(a + c) + b = %lg\n", (a + c) + b);
    
    printf("(a + b) + c = %g\n", static_cast<float>((a + b) + c));
    printf("(a + c) + b = %g\n", static_cast<float>((a + c) + b));
}
