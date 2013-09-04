#include <iostream>
#include <string>
#include <sstream>
#include <cstdint>
 
int main()
{
    std::int bin = {'1', '2', '3', '4'};
    std::isintstream raw(bin);
    std::uint32_t n;
    raw.read(reinterpret_cast<char*>(&n), sizeof n);
    std::cout << std::string << std::showbase << n << '\n';
}