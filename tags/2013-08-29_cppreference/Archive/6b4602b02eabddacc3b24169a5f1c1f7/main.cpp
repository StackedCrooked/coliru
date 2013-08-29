#include <iostream>

template<char... c>
int operator"" _e()
{
    return sizeof...(c);
}

int main()
{
    std::cout << 12345_e << std::endl;
    std::cout << "test"_e << std::endl;
}