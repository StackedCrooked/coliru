#include <tuple>

template<typename... Ts>
std::tuple<Ts...> foo(Ts&&... v) {
    return std::tuple<Ts...>(std::forward<Ts>(v)...); 
}

struct X { int i; };

#include <iostream>
#include <typeinfo>

int main() {
    X x;
    X const y { 56 };
    double splurg;

    std::cout << typeid(foo(X{42}, x, y, splurg)).name();
}

