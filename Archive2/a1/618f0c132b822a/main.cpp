#include <iostream>

template<typename T>
struct Base {
    Base() {
        static_cast<T*>(this)->implementation();
    }

    using F = void(T::*)();

    template<F f>
    void register_method(const char* str) {
        // ...
        std::cout << "registered " << str << '\n';
    }
};

struct Derived : Base<Derived> {
    void foo() {}
    void bar() {}

    void implementation() {
        register_method<&Derived::foo>("foo");
        register_method<&Derived::bar>("bar");
    }
};

int main() {
    Derived x;
}