#include <iostream>
#include <cstddef>
#include <array>




class T {
public:
    static constexpr const char* myList1[] = {
        "A1",
        "A2"
    };
    static constexpr const char* myList2[] = {
        "B1",
        "B2"
    };
};


constexpr const char* result(const int p) {
    return T::myList1[p];
}


int main () {
    std::cout << result(1);
}

/**
 * 
 * 
 * 
 * 
 * 
 * 
 * 
// To catch no argument calls
template <unsigned...>
struct Encrypt;

template <>
struct Encrypt<> {};

template <unsigned size, unsigned... sizes>
struct Encrypt<size, sizes...> {
    
};
*/