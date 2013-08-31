#include <limits>


template <typename T, typename U>
constexpr bool CanTypeFitValue(U value) {
  return ( std::numeric_limits<T>::min() <= (long long)std::numeric_limits<U>::min() || 
           value >= static_cast<U>(std::numeric_limits<T>::min())
         ) && (
           std::numeric_limits<T>::max() >= (unsigned long long)std::numeric_limits<U>::max() || 
           value <= static_cast<U>(std::numeric_limits<T>::max())
         );
}

#include <cassert>
int main(int argc, char** argv) {
    assert(CanTypeFitValue<unsigned char>(-1)==false);
    assert(CanTypeFitValue<unsigned char>(0)==true);
    assert(CanTypeFitValue<unsigned char>(255)==true);
    assert(CanTypeFitValue<unsigned char>(256)==false);
    assert(CanTypeFitValue<unsigned char>(255u)==true);
    assert(CanTypeFitValue<unsigned char>(256u)==false);
    
    assert(CanTypeFitValue<signed char>(-129)==false);
    assert(CanTypeFitValue<signed char>(-128)==true);
    assert(CanTypeFitValue<signed char>(127)==true);
    assert(CanTypeFitValue<signed char>(128)==false);    
    assert(CanTypeFitValue<signed char>(127u)==true);
    assert(CanTypeFitValue<signed char>(128u)==false);
}

