#include <iostream>

struct foo {
    foo(const int n);
};

foo::foo(int n)
{
    n = 1;
    std::cout << "n: " << n << std::endl;
}

int main()
{
    foo f{3};
}