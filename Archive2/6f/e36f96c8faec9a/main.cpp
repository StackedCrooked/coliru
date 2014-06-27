#include <iostream>

int foo(int x)
{ return x/x; }

int main()
{
    auto result = foo(0);
    std::cout << result;
}