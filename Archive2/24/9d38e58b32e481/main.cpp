#include <iostream>
#include <array>

template<char... cs> auto operator"" _cs() -> std::array<char, sizeof...(cs)+1> { return {cs..., '\0'}; }

int main()
{
    std::cout << (55_cs).data();
}