#include <string>
#include <iostream>
#include <cstdint>

int main()
{
    std::uint8_t myVar[10] = "abcdefg";
    std::string res(myVar, myVar + 7);
    std::cout << res;
}