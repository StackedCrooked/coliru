#include <iostream>

template<bool>
struct A
{
    void method() const
    {
        std::cout << "const" << std::endl;
    }
};

template<>
struct A<false>
{
    void method()
    {
        std::cout << "non-const" << std::endl;
    }
};

int main()
{
    A<true> at;
    at.method();
    A<false> af;
    af.method();
}