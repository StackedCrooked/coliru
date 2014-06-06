#include <iostream>
#include <vector>
#include <iterator>

struct Foo
{
    Foo() = default;
    Foo(const Foo&) = default;
    Foo(Foo&&) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
    Foo& operator=(Foo&&) { std::cout << __PRETTY_FUNCTION__ << std::endl; return *this; }
};

int main() 
{
    std::vector<Foo> f1{Foo{}, Foo{}, Foo{}, Foo{}};
    std::vector<Foo> f2{std::make_move_iterator(f1.begin()), std::make_move_iterator(f1.end())};
}
