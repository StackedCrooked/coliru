#include <sstream>
#include <string>
#include <iostream>

int main() {
    std::string bin = {'\x12', '\x13', '\x14', '\x15'};
    std::istringstream raw(bin);
    std::uint32_t n;
    raw.read(reinterpret_cast<char*>(&n), sizeof(n));
    std::cout << std::hex << std::showbase << n << '\n';
}