#include <iostream>

template <typename T, unsigned int ArraySize>
unsigned int Size(T array[ArraySize]) {
    return Size;
}

int main()
{
    std::cout << Size("Hello, world!") << std::endl;
}