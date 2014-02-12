#include <cstddef>
#include <iostream>
#include <string>

void test ( std::string binary, std::string expected, uint32_t boy ) {
    union {
        uint32_t u;
        float cast;
    } cow{boy};
    std::cout << binary << " == " << expected << " == " << cow.cast << std::endl;
}

int main() {
    test( "11101.1010", "29.625", 0b01000001111011010000000000000000 );
}
