#include <iostream>
#include <bitset>

template<int N> struct charset {
    unsigned char values : N;
};

auto main() -> int {
    std::cout << "2: " << sizeof(charset<2>) << '\n';
    std::cout << "4: " << sizeof(charset<4>) << '\n';
    std::cout << "8: " << sizeof(charset<8>) << '\n';
    std::cout << "16: " << sizeof(std::bitset<16>) << '\n';
    std::cout << "32: " << sizeof(std::bitset<32>) << '\n';
    std::cout << "64: " << sizeof(std::bitset<64>) << '\n';
    std::cout << "128: " << sizeof(std::bitset<128>) << '\n';
    std::cout << "256: " << sizeof(std::bitset<256>) << '\n';
}