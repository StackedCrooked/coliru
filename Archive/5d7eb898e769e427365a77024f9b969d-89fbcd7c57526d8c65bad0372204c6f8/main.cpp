#include <iostream>

struct foo
{
    virtual void operator()()
    {
        std::cout << "base" << std::endl;
    }
};

struct bar : foo
{
    virtual void operator()()
    {
        std::cout << "derived" << std::endl;
    }
};

int main()
{
    bar b;
    foo & a = b;
    a();
}