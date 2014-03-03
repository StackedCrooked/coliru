#include <iostream>
#include <type_traits>

struct foo
{
    int x =10;
};

struct bar
{
    int x;
};

int main()
{
    std::cout << std::is_pod<foo>::value << '\n';
    std::cout << std::is_pod<bar>::value << '\n';
}
