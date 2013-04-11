#include <iostream>
#include <string>
#include <vector>

template <typename TTo, typename T>
TTo cowbow_cast ( const T& value ) {
    union {
        T cow;
        TTo boy;
    } cast;
    
    cast.cow = value;
    return cast.boy;
}

int main ( ) {
    std::cout << cowbow_cast<float>( 0x10000 ) << std::endl;
}
