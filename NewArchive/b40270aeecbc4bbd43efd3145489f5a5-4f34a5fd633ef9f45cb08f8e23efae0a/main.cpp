#include <limits>
#include <iostream>
#include <stdint.h>
#include <cstdlib>

#define LLONG_MIN -9223372036854775807ll
#define LLONG_MAX  9223372036854775807ull
#define ULLONG_MAX 18446744073709551615ull

template <typename T, typename U>
bool CanTypeFitValueOrig(const U value) {
    const intmax_t bot_t = intmax_t(std::numeric_limits<T>::min() );
    const intmax_t bot_u = intmax_t(std::numeric_limits<U>::min() );
    const uintmax_t top_t = uintmax_t(std::numeric_limits<T>::max() );
    const uintmax_t top_u = uintmax_t(std::numeric_limits<U>::max() );
    return !( (bot_t > bot_u && value < static_cast<U> (bot_t)) || (top_t < top_u && value > static_cast<U> (top_t)) );        
}
    
#include <iostream>
template <typename T, typename U>
bool CanTypeFitValueDebug(const U value) {
    const long long min = std::numeric_limits<T>::min(); //-128
    const long long max = std::numeric_limits<T>::max(); //127
    const long long v0 (value); //128
    const unsigned long long v1 (v0-min); //256
    const unsigned long long max2 (max-min); //255
    std::cerr << value << ' ' << min << ' ' << max << ' ' << v0 << ' ' << v1 << ' ' << max2 << '\n';
    return v1 <= max2;
}
    
template <typename T, typename U>
constexpr bool CanTypeFitValue(const U value) {
    return  (unsigned long long)((long long)(value                        )-(long long)std::numeric_limits<T>::min()) <=
            (unsigned long long)((long long)(std::numeric_limits<T>::max())-(long long)std::numeric_limits<T>::min());
}

#include <cassert>
int main() {
    assert(CanTypeFitValue<signed char>(-129) == false);
    assert(CanTypeFitValue<signed char>(-128) == true);
    assert(CanTypeFitValue<signed char>(127) == true);
    assert(CanTypeFitValue<signed char>(128) == false);
    assert(CanTypeFitValue<signed char>(127u) == true);
    assert(CanTypeFitValue<signed char>(128u) == false);
    
    assert(CanTypeFitValue<unsigned char>(-1) == false);
    assert(CanTypeFitValue<unsigned char>(0) == true);
    assert(CanTypeFitValue<unsigned char>(255) == true);
    assert(CanTypeFitValue<unsigned char>(256) == false);
    assert(CanTypeFitValue<unsigned char>(255u) == true);
    assert(CanTypeFitValue<unsigned char>(256u) == false);
    
    assert(CanTypeFitValue<signed long long>(LLONG_MIN) == true);
    assert(CanTypeFitValue<signed long long>(LLONG_MAX) == true);
    assert(CanTypeFitValue<unsigned long long>(0) == true);
    assert(CanTypeFitValue<unsigned long long>(ULLONG_MAX) == true);
    
    CanTypeFitValueDebug<signed long long>(ULLONG_MAX) == false;    
    CanTypeFitValueDebug<unsigned long long>(LLONG_MIN) == false;
    CanTypeFitValueDebug<unsigned long long>(-1) == false;
}
    
