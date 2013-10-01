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
    std::cout << "[0]: " << bytes[0] << '\n';
    std::cout << "[1]: " << bytes[1] << '\n';
    std::cout << "[2]: " << bytes[2] << '\n';
    std::cout << "[3]: " << bytes[3] << '\n';
    return (bytes[3] << 24) | (bytes[2] << 16) | (bytes[1] << 8) | bytes[0];
}

int main() {
    std::cout << " host is " << (is_big_endian() ? "big endian\n" : "little endian\n");
    
    unsigned int uliteral = 0x456e7120;
    int sliteral = 0x456e7120;
    std::cout << " unsigned 0x456e7120 = " << uliteral << "\n";
    std::cout << "   signed 0x456e7120 = " << sliteral << "\n";
    
    std::cout << " " << parse_uint32("\x20\x71\x6e\x45") << "\n";
    
    std::stringstream sstr{/*std::ios::binary*/};
    // Write 0x456e7120 in little endian to stream
    sstr.put('\x20');
    sstr.put('\x71');
    sstr.put('\x6e');
    sstr.put('\x45');
    std::cout << " " << parse_uint32(std::istreambuf_iterator<char>(sstr)) << "\n";
    
}