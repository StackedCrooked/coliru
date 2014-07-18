// Compile on a recent version of clang and run it:
// clang++ -std=c++11 -O3 -Wall -fsanitize=undefined stdint16.cpp -o stdint16

#include <type_traits>
#include <cinttypes>
#include <cstdint>
#include <cstdio>

template <typename T, typename std::enable_if<std::is_unsigned<T>::value && (sizeof(T) <= sizeof(unsigned int)) , int>::type = 0>
T safe_multiply(T a, T b) {
    return (unsigned int)a * (unsigned int)b;
}

template <typename T, typename std::enable_if<std::is_unsigned<T>::value && (sizeof(T) > sizeof(unsigned int)) , int>::type = 0>
T safe_multiply(T a, T b) {
    return a * b;
}

int main()
{
     std::uint8_t a =  UINT8_MAX; a = safe_multiply(a, a);
    std::uint16_t b = UINT16_MAX; b = safe_multiply(b, b); // undefined!
    std::uint32_t c = UINT32_MAX; c = safe_multiply(c, c); 
    std::uint64_t d = UINT64_MAX; d = safe_multiply(d, d); 

    //std::int64_t e = INT64_MAX; e = safe_multiply(e, e); // compile error
    
    std::printf("%02" PRIX8 " %04" PRIX16 " %08" PRIX32 " %016" PRIX64 "\n",
        a, b, c, d);

    return 0;
}