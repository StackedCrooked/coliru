#include <cstddef>
#include <iostream>
#include <array>

const long double maximum_piage = 3.141592653589793238462643383279502884197169399375105820974944592307816406286;


template <typename T>
T pi () {
    return static_cast<T>( maximum_piage );
};

int main () {
    
    // *Sniff* Goodbyte, awesome syntax. I hardly knew ye. ;(
    //float f = pi<float>;
    float f = pi<float>();
}

