#include <iostream>
#include <type_traits>

struct T
{
    int x;
};

struct S
{
    static int x;
};

int main()
{
    std::cout << !std::is_member_pointer<decltype(&T::x)>::value << ' ';
    std::cout << !std::is_member_pointer<decltype(&S::x)>::value << '\n';
}