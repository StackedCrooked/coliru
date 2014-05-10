#include <xmmintrin.h>
#include <smmintrin.h>

__m128 a, b;

int main()
{
    __m128 c = _mm_dp_ps(a, b, 0x71);
    return _mm_movemask_ps(c);
}
