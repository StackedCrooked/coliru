#include <iostream>

int foo()
{
    std::cout << "foo! ";
    return 1;
}

int bar()
{
    std::cout << "bar! ";
    return 2;
}

int main()
{
    std::cout << foo() << ' ' << bar();
}