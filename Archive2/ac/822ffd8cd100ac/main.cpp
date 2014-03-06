#include <cstddef>
#include <iostream>
#include <array>

const static double maximum_piage = 3.141592653589793238462643383279502884197169399375105820974944592307816406286;

template <typename T>
struct pi {
    
    operator T () {
        return static_cast<T>( maximum_piage );
    }
};

int main () {
    
    float f = pi<float>;
    
}

