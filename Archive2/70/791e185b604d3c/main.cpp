template<typename Derived, typename Base> struct is_base_of {
    struct yes { char arr[2]; };
    struct no { char c; };
    static yes f(Base* b);
    static no f(...);
    static const auto value = sizeof(f((Derived*)0)) == sizeof(yes);
};
struct base {};
struct derived : base {};
struct notderived {};

#include <iostream>

int main() {
    std::cout << std::boolalpha << is_base_of<derived, base>::value << "\n" << is_base_of<notderived, base>::value;
}