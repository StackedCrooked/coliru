#include <iostream>

struct foo
{
    foo() = default;
    foo(foo const&) { std::cout << "copy-ctor\n"; }
    template<class T>
    foo(T&&) { std::cout << "ctor-template\n"; }
};

int main()
{
    foo f0;
    foo f1(f0);
}