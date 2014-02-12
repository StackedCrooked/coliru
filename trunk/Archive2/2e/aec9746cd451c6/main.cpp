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
    test( "11101.1010 base2 ", 
    "29.625 ", 
    0b01000001111011010000000000000000 );
    test( "-11101.1010 base2", 
    "-22.75 ", 
    0b11000001101101100000000000000000 );
    test( "0.001 base2      ", 
    "0.125  ", 
    0b00111110000000000000000000000000 );
    test( "100011 base2     ", 
    "35     ", 
    0b01000010000011000000000000000000 );
    test( "-1.0011 base2    ", 
    "-1.1875", 
    0b10111111100110000000000000000000 );
}
