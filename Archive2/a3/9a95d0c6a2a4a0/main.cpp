#include <iostream>
#include <string>
#include <sstream>
#include <cstdint>
 
int main()
{
    std::string bin = {'\x12', '\x12', '\x12', '\x12'};
    std::istringstream raw(bin);
    std::uint32_t n;
    raw.read(reinterpret_cast<char*>(&n), sizeof n);
    std::cout << std::hex << std::showbase << n << '\n';
}