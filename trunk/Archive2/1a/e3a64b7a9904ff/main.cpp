#include <cstddef>
#include <iostream>
#include <array>

const static double maximum_piage = 3.141592653589793238462643383279502884197169399375105820974944592307816406286;

template <typename T>
struct pi_t {
    static const pi_t value = pi_t();
    
    operator T () {
        return static_cast<T>( maximum_piage );
    }
};

template <typename T>
using pi = pi_t<float>::value;

int main () {
    
    float f = pi<float>;
    
}

