#include <iostream>

template<class TYPE>
void print_type() { std::cout << __PRETTY_FUNCTION__ << "\n"; }

template<class R, class C>
void foo(R C::*) { print_type<R>(); }

struct bar
{
    void meow() const {}
};

int main()
{
    foo(&bar::meow);
}