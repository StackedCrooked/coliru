#include <iostream>
#include <string>
#include <vector>

template <typename TTo, typename T>
TTo cowboy_cast ( const T& cow) {
    union u {
        T cow;
        TTo boy;
    };
    return u{cow}.boy;
}

int main ( ) {
    std::cout << cowboy_cast<float>( 0x10000 ) << std::endl;
}
