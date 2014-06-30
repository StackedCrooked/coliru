#include <iostream>
#include <memory>
#include <utility>

template <typename T>
void delete_function(void* ptr) {
    // Tell GCC that we know we're doing something stupid and
    // it need not warn us about it.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdelete-non-virtual-dtor"
    delete static_cast<T*>(ptr);
#pragma GCC diagnostic pop
}

template <typename T>
using erased_unique_ptr = std::unique_ptr<T, void(*)(void*)>;

template <typename T, typename... Args>
inline erased_unique_ptr<T>
make_unique_erased(Args&&... args) {
    return erased_unique_ptr<T>(new T(std::forward<Args>(args)...), &delete_function<T>);
}

struct A {
    ~A() { std::cout << "~A\n"; }
    virtual void f() { std::cout << "A::f\n"; }
    void g() { std::cout << "A::g\n"; }
};

struct B : A {
    ~B() { std::cout << "~B\n"; }
    void f() override { std::cout << "B::f\n"; }
    void g() { std::cout << "B::g\n"; }
};

int main() {
    erased_unique_ptr<A> p = make_unique_erased<B>();
    p->f();
    p->g();
}
