#include <iostream>

struct X
{
    using type = int;
};

struct Y : X
{
    type foo() { return 42; }
};

int main()
{
    Y y;
    std::cout << y.foo();
}