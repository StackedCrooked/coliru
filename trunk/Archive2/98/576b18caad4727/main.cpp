#include <type_traits>
#include <iostream>

class Base {};

class Derived : public Base {};

template <typename T>
typename std::enable_if<!std::is_base_of<Base, T>::value>::type
    f(const T& value) {
    std::cout << __PRETTY_FUNCTION__ << '\n';
}

void f(const Base& value) {
    std::cout << __PRETTY_FUNCTION__ << '\n';
}

int main() {
    Base b;
    f(b);

    Derived d;
    f(d); // This line causes linker error.

    return 0;
}
