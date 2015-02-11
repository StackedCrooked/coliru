#include <iostream>
#include <string>
#include <vector>

struct S
{
    uint32_t a;
    uint16_t b;
    uint8_t c;
    uint16_t d;
};

int main()
{
    std::cout << sizeof(S) << std::endl;
}
