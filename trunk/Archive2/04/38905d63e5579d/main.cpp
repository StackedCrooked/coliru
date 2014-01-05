#include <stdio.h>
#include <stdlib.h>
#include <emmintrin.h>                 // SSE2
#include <omp.h>

int countZeroBytes(char* values, int length) {
    int zeroCount = 0;
    for(int i=0; i<length; i++) {
        if (!values[i])
            ++zeroCount;
    }
    return zeroCount;
}

int countZeroBytes_fix(char* values, int length) {
    int zeroCount = 0;
    for(int i=0; i<length; i++) {
        zeroCount += values[i] == 0;
    }
    return zeroCount;
}

int countZeroBytes_SSE(char* values, int length) {
    int zeroCount = 0;
    __m128i zero16 = _mm_set1_epi8(0);
    __m128i and16 = _mm_set1_epi8(1);
    for(int i=0; i<length; i+=16) {
        __m128i values16 = _mm_loadu_si128((__m128i*)&values[i]);
        __m128i cmp = _mm_cmpeq_epi8(values16, zero16);
        int mask = _mm_movemask_epi8(cmp);
        if(mask) {
            if(mask == 0xffff) zeroCount += 16;
            else {
                cmp = _mm_and_si128(and16, cmp); //change -1 values to 1
                //hortiontal sum of 16 bytes
                __m128i sum1 = _mm_sad_epu8(cmp,zero16);
                __m128i sum2 = _mm_shuffle_epi32(sum1,2);
                __m128i sum3 = _mm_add_epi16(sum1,sum2);
                zeroCount += _mm_cvtsi128_si32(sum3);
            }
        }
    }
    return zeroCount;
}

int main() {
    const int n = 1<<16;
    const int repeat = 10000;
    char *values = (char*)_mm_malloc(n, 16);
    //for(int i=0; i<n; i++) values[i] = rand()%64;  //1.5% zeros
    for(int i=0; i<n/2; i++) values[i] = 1;
    for(int i=n/2; i<n; i++) values[i] = 0;

    int zeroCount = 0;
    double dtime;
    dtime = omp_get_wtime();
    for(int i=0; i<repeat; i++) zeroCount = countZeroBytes(values,n);
    dtime = omp_get_wtime() - dtime;
    printf("zeroCount %d, time %f\n", zeroCount, dtime);
    dtime = omp_get_wtime();
    for(int i=0; i<repeat; i++) zeroCount = countZeroBytes_fix(values,n);
    dtime = omp_get_wtime() - dtime;
    printf("zeroCount_fix %d, time %f\n", zeroCount, dtime);
    dtime = omp_get_wtime();
    for(int i=0; i<repeat; i++) zeroCount = countZeroBytes_SSE(values,n);
    dtime = omp_get_wtime() - dtime;
    printf("zeroCount_SSE %d, time %f\n", zeroCount, dtime);

}