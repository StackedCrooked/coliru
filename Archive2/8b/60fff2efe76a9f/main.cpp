#include <iostream>

template <typename T>
struct Base
{
    int x = 42;
};

template <typename T>
struct Derived : public Base<T>
{
    void foo();
};

template <typename T>
void Derived<T>::foo()
{
    std::cout << x << '\n';
}

int main()
{
    Derived<void> d;
    d.foo();
}
