#include <iostream>
#include <complex>

struct X {
    int i;
    float f;
    std::complex<double> c;
};

constexpr X x = { 99, 88.8, {77.7, 1.0} };

int main()
{
    std::cout << x.f << '\n';   
}