#include <xmmintrin.h>
#include <smmintrin.h>

__m128 a, b;

float chk(__m128 a, __m128 b)
{
    auto t0 = _mm_mul_ps(a, b);
    return t0[0] + t0[1] + t0[2];
    //auto t1 = _mm_shuffle_ps(a, a, _MM_SHUFFLE(0, 0, 0, 1));
    //auto t2 = _mm_shuffle_ps(a, a, _MM_SHUFFLE(0, 0, 0, 2));
    //auto t3 = _mm_add_ps(t0, t1);
    //auto t4 = _mm_add_ps(t3, t2);
    //return _mm_cvtss_f32(t4);
}

int main()
{
    __m128 c = _mm_dp_ps(a, b, 0x71);
    return _mm_movemask_ps(c);
}
