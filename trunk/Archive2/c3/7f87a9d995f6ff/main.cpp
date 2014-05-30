#include <xmmintrin.h>
#include <smmintrin.h>

typedef float float1 __attribute__((vector_size(4)));
typedef float float2 __attribute__((vector_size(8)));
typedef float float4 __attribute__((vector_size(16)));
typedef float float8 __attribute__((vector_size(32)));
typedef int int1 __attribute__((vector_size(4)));
typedef int int2 __attribute__((vector_size(8)));
typedef int int4 __attribute__((vector_size(16)));
typedef int int8 __attribute__((vector_size(32)));

int main()
{
    float4 x = { 1, 2, 3, 4 };
    float4 y = { 4, 5, 6, 7 };
    x += y;
}
