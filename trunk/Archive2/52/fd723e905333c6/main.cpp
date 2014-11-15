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

struct Derived1 : Base<Derived1> {
public:
    static void register_all() {
        std::cout << "D1" << '\n';
        register_method<&Derived1::foo>("foo");
        register_method<&Derived1::bar>("bar");
    }
public:
    void foo() {}
    void bar() {}
};
struct Derived2 : Base<Derived2> {
public:
    static void register_all() {
        std::cout << "D2" << '\n';
        register_method<&Derived2::woot>("woot");
    }
public:
    void woot() {}
};

// have to initialise static-s outside class...
template<typename T>
std::once_flag Base<T>::flag_{};


int main() {
    Derived1 x;
    Derived1 y;
    
    Derived2 z;
}