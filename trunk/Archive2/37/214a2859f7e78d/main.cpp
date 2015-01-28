#include <iostream>

template<typename T> void f(T* const& c){ std::cout << "pointer\n"; }
template<typename T, size_t N> void f(T(&)[N]){ std::cout << "array\n"; }

int main()
{
    double const  d[] = {1.,2.,3.};
    double a;
    double const* p = &a;
    f(d); // call array version
    f(p); // call pointer version
}