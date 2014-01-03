#include <iostream>

struct Foo {
    enum { number = 42 };
};

int main()
{
    Foo bar;
    std::cout << bar.number << std::endl;
}