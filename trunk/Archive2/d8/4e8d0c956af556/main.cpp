#include <iostream>

struct Base {
    virtual ~Base() = default;
    template <typename T, typename... Args, typename R> void helper (R T::*, Args...);
    void bar (int n) {std::cout << "bar " << n << std::endl;}
};

struct Derived : Base {
    void baz (double d, int n) {std::cout << "baz " << d << ' ' << n << std::endl;}
};

template <typename T, typename... Args, typename R>
void Base::helper (R T::*f, Args... args) {
    // A bunch on lines here (hence the motivation for the helper function)
    for (int n = 0;  n < 5;  n++)
        (dynamic_cast<T*>(this)->*f)(args..., n);
    // ...
}

int main() {
    Base b;
    Derived d;
    b.helper(&Base::bar);  // GCC 4.8.1 will accept this, Visual Studio 2013 won't.
    d.helper<Derived, double>(&Derived::baz, 3.14);  // Visual Studio 2013 will accept this, GCC 4.8.1 won't
}