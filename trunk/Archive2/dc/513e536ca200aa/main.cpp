#include <cstddef>

#include <iostream>
#define Explicit( i ) std::cout << i << std::endl

template <std::size_t i, std::size_t decr = 1>
struct static_for_E {
    
    static void invoke () {
        Explicit( i );
        static_for_E<i - decr, decr>::invoke();
    }
    
};

template <std::size_t decr>
struct static_for_E<0, decr> {
    
    static void invoke () {
        
    }
    
};

int main () {
    
    static_for_E<10>::invoke();
    
}