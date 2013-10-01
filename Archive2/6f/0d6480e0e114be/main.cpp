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

template<typename Iter>
unsigned int parse_uint32(Iter i) {
    std::array<unsigned, 4> bytes;
    std::copy_n(i, 4, std::begin(bytes));
    return (bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) | bytes[3];
}

int main() {
    std::cout << " host is " << (is_big_endian() ? "big endian\n" : "little endian\n");
    
    unsigned int uliteral = 0x456e7120;
    int sliteral = 0x456e7120;
    std::cout << " unsigned 0x456e7120 = " << uliteral << "\n";
    std::cout << "   signed 0x456e7120 = " << sliteral << "\n";
    
    std::stringstream sstr(std::ios::binary);
    // Write 0x456e7120 in little endian to stream
    sstr << 0x20 << 0x71 << 0x6e << 0x45 << std::flush;
    std::cout << " " << parse_uint32(std::istreambuf_iterator<char>(sstr)) << "\n";
    return 0;
}