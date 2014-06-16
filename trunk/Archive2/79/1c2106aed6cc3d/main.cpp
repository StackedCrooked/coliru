#include <iostream>

struct foo
{
    int i;
    foo(int i = 0) : i(i)
    {
        std::cout << __PRETTY_FUNCTION__ << '\n';
    }
    foo& operator=(int i)
    {
        std::cout << __PRETTY_FUNCTION__ << '\n';
        this->i = i;
        return *this;
    }
};

int operator,(foo const& a, foo const& b)
{
    std::cout << __PRETTY_FUNCTION__ << '\n';
    return a.i + b.i;
}

int main() 
{
    {
        foo a, b, c, d;
    }
    {
        foo a = 1, b = 2, c = 3, d = 4;
        std::cout << (a, b, c, d) << '\n';
        std::cout << (a = 10, b = 20, c = 30, d = 40) << '\n';
    }
}
