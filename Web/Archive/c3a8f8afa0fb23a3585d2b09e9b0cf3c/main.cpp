#include <iostream>
#include <type_traits>


struct Int
{
    Int() = default;
    int a = 5;s
};


int main()
{
    Int n;    
    std::cout << n.a << std::endl;
    std::cout << Int().a << std::endl;
}