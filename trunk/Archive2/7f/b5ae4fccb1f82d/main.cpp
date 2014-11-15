#include <iostream>
#include <mutex>

template<typename T>
struct Base {
    Base() {
        std::call_once(flag_, T::register_all );
    }

    using F = void(T::*)();

    template<F f>
    static void register_method(const char* str) {
        // ...
        std::cout << "registered " << str << '\n';
    }
public:
    static std::once_flag flag_;
};

struct Derived : Base<Derived> {
public:
    static void register_all() {
        register_method<&Derived::foo>("foo");
        register_method<&Derived::bar>("bar");
    }
public:
    void foo() {}
    void bar() {}
};

// have to initialise static-s outside class...
template<>
std::once_flag Base<Derived>::flag_{};

int main() {
    Derived x;
    Derived y;
}