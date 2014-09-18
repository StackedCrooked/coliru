#include <sstream>
#include <string>
#include <iostream>
#include <algorithm>

template<typename T>
void switch_endianness(T& obj) {
  unsigned char* memp = reinterpret_cast<unsigned char*>(&obj);
  std::reverse(memp, memp + sizeof(T));
}

int main() {
    std::string bin = {'\x12', '\x13', '\x14', '\x15'};
    std::istringstream raw(bin);
    std::uint32_t n;
    raw.read(reinterpret_cast<char*>(&n), sizeof(n));
    std::cout << std::hex << std::showbase << n << '\n';
    switch_endianness(n);
    std::cout << std::hex << std::showbase << n << '\n';
}