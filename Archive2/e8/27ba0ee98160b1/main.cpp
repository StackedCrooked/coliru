#include <iostream>
#include <sstream>
#include <iterator>
#include <array>
#include <cstdint>
#include <endian.h>

int parse_32(std::istream_iterator<char>& it) {
    std::array<char, sizeof(int32_t)> chars;
    for(unsigned i = 0; i < sizeof(int32_t); i++) {
        chars[i] = *it++;
    }
    return le32toh(*reinterpret_cast<int32_t*>(&chars));
}
int main() {
    std::stringstream sstr;
    sstr << 0x20 << 0x71 << 0x6e << 0x45;
    std::istream_iterator<char> it(sstr);
    // Output should be 1164865824
    std::cout << parse_32(it) << "\n";
    return 0;
}