#include <iostream>
#include <type_traits>


struct Int
{
    Int() = default;
    int a = 0;
};


int main()
{
    Int n;
    std::cout << n.a << std::endl;
}