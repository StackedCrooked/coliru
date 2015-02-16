#include <iostream>

struct X
{
    X() {}
    X(X&&) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
};

X f()
{
    X x;
    return x;
}

template<class T>
struct Try
{
    Try(T const&) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
    Try(T&&) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
};

Try<X> h()
{
    X x;
    return x;
}

int main()
{
    f();
    h();
}