#include <iostream>
#include <stdint.h>
#include <iomanip>
#include <xmmintrin.h>


#include <iostream>
#include <smmintrin.h>

template<unsigned i>
float vectorGetByIndex( __m128 V)
{
#ifdef __SSE4_1__
    return _mm_extract_ps(V, i);
#else
    union {
        __m128 v;    
        float a[4];  
    } converter;
    converter.v = V;
    return converter.a[i]
#endif
}

int main()
{
    __m128 test = _mm_set_ps(3.0f, 2.0f, 1.0f, 0.0f);
    std::cout << vectorGetByIndex<1>(test) << std::endl;
}
