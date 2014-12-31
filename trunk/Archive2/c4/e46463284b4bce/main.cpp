#include <iostream>
#include <bitset>
#include <cstdint>
#include <type_traits>

template<char... Chars, int X, int Y>
void operator "" _int() {
    char x[] = {Chars..., '\0'};
    std::cout << x;
}

int main() {
    123_int<3, 4>;
}