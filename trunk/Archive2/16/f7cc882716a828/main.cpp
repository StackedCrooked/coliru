#include <iostream>

struct Test
{
    Test() = default;
    Test(Test const &)
    {
        std::cout << "Copy ctor called" << std::endl;
    }
};

Test f()
{
    return Test();
}

int main()
{
    Test t = f();
}
