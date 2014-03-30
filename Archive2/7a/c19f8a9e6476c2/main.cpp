#include <iostream>

template <typename T> constexpr T epsilon;

template <> constexpr float  epsilon<float>  = 0.001f;
template <> constexpr double epsilon<double> = 0.000001;

template <typename T> void print( T ) {
    std::cout << epsilon<T> << std::endl;
}

int main() {
    print( 1.f );
    print( 1.0 );
}
