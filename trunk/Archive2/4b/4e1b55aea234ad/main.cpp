#include <cstdint>
#include <array>
#include <iostream>


std::array<uint8_t, 6> sdkljf = {{'h','e','l','l','o','\0'}};

int main()
{
    std::cout << sdkljf[1] << sdkljf[2] << std::endl;
}
