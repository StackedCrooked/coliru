#include <iostream>
#include <array>

const char* operator"" _cs(const char* lit) { return lit; }

int main()
{
    std::cout << 55_cs;
}