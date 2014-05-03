#include <iostream>

template<bool>
struct A_base
{
    void method() const
    {
        std::cout << "const" << std::endl;
    }
};

template<>
struct A_base<false>
{
    void method()
    {
        std::cout << "non-const" << std::endl;
    }
};

template<bool isConst>
struct A : A_base<isConst>
{
    void another_method() const
    {
        std::cout << "another method" << std::endl;
    }
};

int main()
{
    A<true> at;
    at.method();
    at.another_method();
    A<false> af;
    af.method();
    af.another_method();
}