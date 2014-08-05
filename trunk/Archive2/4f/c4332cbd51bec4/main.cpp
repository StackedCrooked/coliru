#include <vector>
#include <string>
#include <initializer_list>
#include <iostream>

struct foo
{
    foo(int, int) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
    foo(foo const&) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
    foo(std::initializer_list<std::string>) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
};

int main()
{
    foo f1 = {1,2};
    std::cout << "----\n";
    foo f2({1,2});
    std::cout << "----\n";
    foo f3{1,2};
}
