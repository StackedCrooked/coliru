#include <iostream>

template <typename T>
struct A
{
    template <typename u>
    void foo() { std::cout << "foo\n"; }
};

template <typename T>
struct B : A<T>
{
    void bar()
    {
        foo<T>(); // jak należy wywołać te metode?
    }
};

int main()
{
    B<int> b;
    b.bar();
}