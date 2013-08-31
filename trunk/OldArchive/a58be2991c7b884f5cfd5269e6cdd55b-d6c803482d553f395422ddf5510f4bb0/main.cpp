#include <iostream>
#include <cstring>
#include <type_traits>

template<typename T>
using DisableIf = typename std::enable_if<!T::value>::type;

typedef int special_t;

template <typename T>
struct Arf {
    
    void Woof ( special_t a ) {
    // every class must have this   
    }
    
    template<typename U = T, DisableIf<std::is_convertible<special_t, U>>...>
    void Woof ( T a ) {
    // every class must have a version that takes the T   
    }
};

int main() {
    Arf<short> yay;
    yay.Woof( 1 );
    Arf<int> ohno; // :C
    yay.Woof( 1 );
    
}