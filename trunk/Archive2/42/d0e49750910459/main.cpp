#include <iostream>
#include <type_traits>
#include <vector>

struct Foo 
{
    Foo(Foo&& f) = delete;
};

int main()
{

    std::cout << std::is_move_constructible<Foo>::value;

    std::cin.ignore();
}