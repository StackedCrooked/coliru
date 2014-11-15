#include <iostream>
#include <mutex>

template<typename T>
struct Base {
    Base() {
        static_cast<T*>(this)->register_all();
    }

    using F = void(T::*)();

    template<F f>
    void register_method(const char* str) {
        // ...
        std::cout << "registered " << str << '\n';
    }
};

struct Derived : Base<Derived> {
private:
    static std::once_flag flag_;
    void implementation() {
        register_method<&Derived::foo>("foo");
        register_method<&Derived::bar>("bar");
    }
public:
    void foo() {}
    void bar() {}
    
    void register_all() {
        std::call_once(flag_, [this]{ implementation(); });
    }
};

std::once_flag Derived::flag_;

int main() {
    Derived x;
    Derived y;
}