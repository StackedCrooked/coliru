#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <array>

bool is_big_endian() {
    static const uint16_t m_endianCheck(0x00ff);
    return ( *((uint8_t*)&m_endianCheck) == 0x0); 
}



unsigned int parse_uint32(std::istream_iterator<char> i) {
    std::array<char, 4> bytes;
    std::copy_n(i, 4, std::begin(bytes));
    return (bytes[3] << 24) | (bytes[2] << 16) | (bytes[1] << 8) | bytes[0];
}

int main() {
    std::cout << "host is " << (is_big_endian() ? "big endian\n" : "little endian\n");
    
    unsigned int testa = 0x456e7120;
    int testb = 0x456e7120;
    std::cout << "testa " << testa << "\n";
    std::cout << "testb " << testb << "\n";
    
    std::stringstream sstr(std::ios::binary);
    //sstr << 0x45 << 0x6e << 0x71 << 0x20 << std::flush;
    sstr << 0x20 << 0x71 << 0x6e << 0x45 << std::flush;
    std::cout << parse_uint32(std::istream_iterator<char>(sstr)) << "\n";
    return 0;
}