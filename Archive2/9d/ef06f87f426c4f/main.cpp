#include <iostream>
#include <stdint.h>

enum Enum16 : uint16_t
{
    test = 7
};

template<typename T>
void print(const T&)
{
    std::cout << __PRETTY_FUNCTION__ <<  " size=" << sizeof(T) << std::endl;
}

void print(uint16_t)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

int main()
{
    print(test);
}