#include <type_traits>
#include <iostream>
#include <ios>

struct A
{
  int i;
};

struct B
{
 B(){} 
 int i;
};

struct C
{
 C() = default;
 int i;
};

int main()
{
    std::cout << std::boolalpha << std::is_pod<A>::value << " ";
    std::cout << std::boolalpha << std::is_trivial<A>::value << " ";
    std::cout << std::boolalpha << std::is_standard_layout<A>::value << "\n";

    std::cout << std::boolalpha << std::is_pod<B>::value << " ";
    std::cout << std::boolalpha << std::is_trivial<B>::value << " ";
    std::cout << std::boolalpha << std::is_standard_layout<B>::value << "\n";

    std::cout << std::boolalpha << std::is_pod<C>::value << " ";
    std::cout << std::boolalpha << std::is_trivial<C>::value << " ";
    std::cout << std::boolalpha << std::is_standard_layout<C>::value << "\n";
}