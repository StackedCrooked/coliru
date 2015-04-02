#include <iostream>
#include <bitset>
#include <fstream>
#include <sstream>

int main()
{
    //std::ifstream f("123.bin", std::ios::binary);
    std::stringstream f;
    f << 56L;

    unsigned long cache = 0;
    f >> cache;
    std::bitset<8> bits(cache);
    std::cout << bits << std::endl;
}
