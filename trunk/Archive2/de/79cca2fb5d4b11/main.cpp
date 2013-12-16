#include <stdio.h>
int main() {     
    typedef float float4 __attribute__ ((vector_size (16)));
    
    float4 x = {1,2,3,4};
    float4 y = (25.0f/216.0f)*x;
    printf("%f %f %f %f\n", y[0], y[1], y[2], y[3]);
}