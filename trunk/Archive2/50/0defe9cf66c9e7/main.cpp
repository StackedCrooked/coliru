#include <iostream>

struct Unit {
};

//void foo(Unit) {
//    std::cout << "value\n";
//}
void foo(Unit&) {
    std::cout << "lvalue ref\n";
}
void foo(const Unit&) {
    std::cout << "const lvalue ref\n";
}
void foo(volatile Unit&) {
    std::cout << "volatile lvalue ref\n";
}
void foo(const volatile Unit&) {
    std::cout << "const volatile lvalue ref\n";
}
void foo(Unit&&) {
    std::cout << "rvalue ref\n";
}
void foo(const Unit&&) {
    std::cout << "const rvalue ref\n";
}
void foo(volatile Unit&&) {
    std::cout << "volatile rvalue ref\n";
}
void foo(const volatile Unit&&) {
    std::cout << "const volatile rvalue ref\n";
}

int main() {
    Unit x;
    foo(x);
    foo(static_cast<const Unit&>(x));
    foo(static_cast<volatile Unit&>(x));
    foo(static_cast<const volatile Unit&>(x));
    foo(Unit());
    foo(static_cast<const Unit&&>(Unit()));
    foo(static_cast<volatile Unit&&>(Unit()));
    foo(static_cast<const volatile Unit&&>(Unit()));
}