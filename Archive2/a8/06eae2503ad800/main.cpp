#include <iostream>
template <typename T>
class Base2 {
public:
    void foo(T ) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
};

template <typename... Bases>
struct BaseCollector { };

template <typename Base>
struct BaseCollector<Base> : Base {};

template <typename Base, typename... Bases>
struct BaseCollector<Base, Bases...> : Base, BaseCollector<Bases...>
{
    using Base::foo;
    using BaseCollector<Bases...>::foo;
};

struct Derived : BaseCollector<Base2<int>, Base2<double>>
{ };

int main() {
    Derived().foo(0); // OK
    Derived().foo(0.0); // OK
}