#include <tuple>

template<typename... Ts>
std::tuple<Ts...> foo(Ts&&... v) {
    return std::tuple<Ts...>(std::forward<Ts>(v)...); 
}


#include <iostream>
#include <typeinfo>
struct X { int i; };
template <typename T> using alias = T;

int main() {
    X x;
    X const y { 56 };
    double splurg[10];

    std::cout << typeid(foo(X{42}, x, y, splurg, alias<int[3]> { 1,2,3 })).name();
}

