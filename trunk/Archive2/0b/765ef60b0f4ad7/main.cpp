#include <iostream>

struct Test
{
    Test() = default;
    Test(Test const &)
    {
        std::cout << "Copy ctor called" << std::endl;
    }
};

void f(Test t)
{
}

int main()
{
    Test my;
    std::cout << "A" << std::endl;
    f(my);
    std::cout << "B" << std::endl;
    f(Test());
    std::cout << "C" << std::endl;
}
