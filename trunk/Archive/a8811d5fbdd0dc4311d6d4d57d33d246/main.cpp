#include <iostream>

constexpr char operator"" _e(const char* str, size_t)
{
    return str[1];
}

int main()
{
    constexpr auto x = "test"_e;
    std::cout << x << std::endl;
}