#include <type_traits>
class Base
{
public:
    template <typename X>
    void fun() {}
};

template <typename T>
class Derived : public Base
{
public:
    template <typename X, typename Y =T, typename std::enable_if<std::is_floating_point<Y>::value, void>::type* = nullptr>
    void fun() {}
};

int main()
{
    Derived<double> d1;
    Derived<int> d2;
    d1.fun<double>();
    d2.fun<double>();
    return 0;
}