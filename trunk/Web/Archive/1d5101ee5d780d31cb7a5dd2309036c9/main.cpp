#include <iostream>


struct {
    void operator()()
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    void operator()(int)
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    } foo;

struct {
    void operator()() { std::cout << __PRETTY_FUNCTION__ << std::endl; }
} bar;

int main()
{
    foo();
    bar();
}