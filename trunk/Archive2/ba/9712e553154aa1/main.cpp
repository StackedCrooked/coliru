#include <iostream>

template <typename T, unsigned int ArraySize>
unsigned int Size(T array[ArraySize]) {
    return ArraySize;
}

int main()
{
    std::cout << Size("Hello, world!") << std::endl;
}