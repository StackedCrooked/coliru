#include <type_traits>
#include <iostream>

template<typename T>
struct test {
    static constexpr bool is_pointer{std::is_pointer<T>::value};
};

template<typename T>
constexpr bool test<T>::is_pointer;

template<typename T>
constexpr bool foo{test<T>::is_pointer};

int main() {
    std::cout << foo<bool>;
    std::cout << foo<bool*>;
}