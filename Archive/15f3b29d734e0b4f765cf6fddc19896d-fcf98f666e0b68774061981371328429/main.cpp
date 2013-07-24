#include <iostream>
#include <type_traits>

template<typename T>
struct identity { using type = T; };

template <typename T>
struct A {
    int val = 0;

    template<typename = typename std::enable_if<identity<T>::type::value>::type>
    A(int n) : val(n) {}
    A(...): val(0) { }
};

struct YES { constexpr static bool value = true; };
struct NO { constexpr static bool value = false; };

int main() {
    A<YES> y(10);
    A<NO> n;
    std::cout << "YES: " << y.val << std::endl
              << "NO:  " << n.val << std::endl;
}