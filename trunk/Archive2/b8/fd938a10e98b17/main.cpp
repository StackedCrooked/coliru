#include <emmintrin.h>
#include <stdio.h>

__m128i bit_mask(int n)
{
    __m128i v0 = _mm_set_epi64x(-1, -(n > 64)); // AND mask
    __m128i v1 = _mm_set_epi64x(-(n > 64), 0);  // OR mask
    __m128i v2 = _mm_slli_epi64(_mm_set1_epi64x(-1), (128 - n) & 63);
    v2 = _mm_and_si128(v2, v0);
    v2 = _mm_or_si128(v2, v1);
    return v2;
}

int main(int argc, char *argv[])
{
    int n = 36;

    if (argc > 1) n = atoi(argv[1]);

    printf("bit_mask(%3d) = %02vx\n", n, bit_mask(n));

    return 0;
}