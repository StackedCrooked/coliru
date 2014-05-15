#include <cstddef>

#define Explicit( i ) std::cout << i

template <std::size_t i, std::size_t decr>
struct static_for_E {
    
    static void invoke () {
        Explicit( i );
        static_for_E<i - decr>::invoke();
    }
    
}

#include <iostream>

int main () {
    
    static_for_E<10, 1>::invoke();
    
}