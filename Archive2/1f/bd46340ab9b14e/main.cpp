#include <complex>
#include <iostream>
#include <typeinfo>

using namespace std;

template<typename T>
void print_type() { std::cout << __PRETTY_FUNCTION__ << "\n"; }

int main()
{
    print_type<decltype(complex<double>(0.0,1.0))>();
    print_type<decltype(1.0i)>();
    cout << boolalpha;
    cout << (typeid(complex<double>(0.0,1.0)) == typeid(1.0i)) << "\n";
}