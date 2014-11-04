#include <utility>
#include <algorithm>
#include <type_traits>

namespace detail {
    template<typename T> auto
    check(int) -> decltype(swap(std::declval<T&>(), std::declval<T&>()), std::true_type());
    template<typename T> std::integral_constant<bool,
        std::is_move_assignable<T>::value && std::is_move_constructible<T>::value>
    check(...);
    template<typename T> struct is_swappable : decltype(check<T>(0)) {};
}

struct A {
//    A(const A&) = delete;
//    A(A&&) = delete;
};

#include <iostream>
int main(int argc, char** argv) {
    std::cout << detail::is_swappable<A>::value;
}
