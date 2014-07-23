#include <iostream>
#include <string>
#include <sstream>
 
int main()
{
    std::string bin = {'\x00', '\x00', '\x00', '\x29'};
    std::istringstream raw(bin);
    std::uint32_t n;
    raw.read(reinterpret_cast<char*>(&n), sizeof(n));
    std::cout << n << '\n';
    std::cout << std::hex << std::showbase << n << '\n';
    // bad order as you can see.
    std::cout << "----------\n----------\n";
    // do it this way instead:
    std::string data = { '\x00', '\x00', '\x00', '\x29' };
    std::istringstream ss(bin);
    char arr[4];
    ss.read(arr, sizeof(arr));
    std::uint32_t x = (arr[3] << 0) | (arr[2] << 8) | (arr[1] << 16) | (arr[0] << 24);
    std::cout << std::dec << x << '\n';
    std::cout << std::hex << std::showbase << x << '\n';
}