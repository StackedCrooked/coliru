#include <iostream>
#include <sstream>
#include <iterator>
#include <array>
#include <cstdint>
#include <endian.h>

uint32_t parse_32(std::istream_iterator<char>& it) {
    std::array<char, sizeof(uint32_t)> chars;
    for(unsigned i = 0; i < sizeof(uint32_t); i++) {
        chars[i] = *it++;
    }
    return le32toh(*reinterpret_cast<uint32_t*>(&chars));
}
int main() {
    std::stringstream sstr;
    sstr << 0x20 << 0x71 << 0x6e << 0x45;
    std::istream_iterator<char> it(sstr);
    std::cout << 0x456e7120 << "\n";
    std::cout << parse_32(it) << "\n";
    return 0;
}