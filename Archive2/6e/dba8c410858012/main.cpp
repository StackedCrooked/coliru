#include <array>
#include <iostream>

template <unsigned int NBytes>
struct Filler
{
    std::array<unsigned char, NBytes> _;
};

struct Foo
{
    float f;
    Filler<4>;
};

struct Bar
{
    double d;
    struct { Filler<4> _; };
};

int main()
{
    std::cout << sizeof(Foo) << std::endl;
    std::cout << sizeof(Bar) << std::endl;
    return 0;
}