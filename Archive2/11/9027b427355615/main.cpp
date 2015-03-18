#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <type_traits>

template<typename... Ts>
struct AllEqual;

template<typename Head1, typename Head2, typename... Tail>
struct AllEqual<Head1, Head2, Tail...> {
    static constexpr bool value = std::is_same<Head1, Head2>::value && AllEqual<Head2, Tail...>::value;
};

template<typename Head1>
struct AllEqual<Head1> {
    static constexpr bool value = true;
};

template<typename... Ts>
typename std::enable_if<AllEqual<Ts...>::value, void>::type foo(Ts&&...) {
    std::cout << "yes";
}

template<typename... Ts>
typename std::enable_if<!AllEqual<Ts...>::value, void>::type foo(Ts&&...) {
    std::cout << "no";
}

int main()
{
    foo(1, 2, 3, "asdf");
}
