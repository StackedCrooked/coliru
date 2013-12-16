#include <immintrin.h>
//#include <x86intrin.h>

template<bool foo>
void bar() {
    _mm256_macc_ps(__m256(), __m256(), __m256());
}

int main() {
}