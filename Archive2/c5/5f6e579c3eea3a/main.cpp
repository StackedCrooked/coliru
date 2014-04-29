#include <type_traits>

template <typename T>
int  f_impl(T t, std::true_type) {
    return 42 + t;
}
template <typename T>
double f_impl(T, std::false_type) {
    return 3.14;
}
template <typename T>
auto f(T t) -> decltype(f_impl(t, std::is_integral<T>())) {
    return f_impl(t, std::is_integral<T>());
}

#include <iostream>

int main() {
    std::cout << f(1) << " " << f(1.2);
}
