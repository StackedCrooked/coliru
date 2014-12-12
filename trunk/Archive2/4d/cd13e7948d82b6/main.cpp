#include <iostream>
#include <type_traits>

template <typename...>
struct A { using base = A; };

struct A1 : A<int, double> { };
struct A2 : A<int, float> { };

struct T { };

template <typename Base>
struct U_helper;

template <typename... Interfaces>
struct U_helper<A<Interfaces...>> : A<T, Interfaces...> { };

template <typename Base>
using U = U_helper<typename Base::base>;

int
main() {
    std::cout << std::is_base_of<A<T, int, double>, U<A1>>::value << '\n';
}
