#pragma pack(4)
struct example
{
    int a;
    long b;
    int c;
};

#include <iostream>
#include <cstddef>

int main()
{
    std::cout << offsetof(example, a) << '\n';
    std::cout << offsetof(example, b) << '\n';
    std::cout << offsetof(example, c) << '\n';
    std::cout << sizeof(example) << '\n';
}