#include <type_traits>
#include <iostream>
using std::cout;
using std::endl;
class Base
{
public:
    template <typename X>
    void fun() { std::cout << "Base fun()" << std::endl; }
};

template <typename T, bool is_float = std::is_floating_point<T>::value>
class Derived : public Base
{
public:
    template <typename X>
    void fun() { std::cout << "Derived fun()" << std::endl;}
};

template <typename T>
class Derived<T, false> : public Base
{

};

int main()
{
    Derived<double> d1;
    Derived<int> d2;
    d1.fun<double>();
    d2.fun<double>();
    return 0;
}