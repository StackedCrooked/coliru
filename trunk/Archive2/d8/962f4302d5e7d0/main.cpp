#include <iostream>
#include <complex>

template<class T>
void foo(const T&)
{
    std::cout << __PRETTY_FUNCTION__ << '\n';
}

int main()
{
    foo(std::complex<double>(0.0,1.0));
    foo(1.0i);
}