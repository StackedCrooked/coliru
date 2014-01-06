#include <type_traits>
#include <iostream>

#define IS_SAME(x,y) std::cout << std::is_same<x,y>::value << '\n';

int main()
{
    IS_SAME(char16_t, char);
    IS_SAME(char16_t, short);
    IS_SAME(char16_t, unsigned short);
    IS_SAME(char, unsigned char);
    IS_SAME(char, signed char);
}
