#include <initializer_list>
#include <iostream>

struct base {
    virtual void f() const {
        std::cout << "base\n";
    }
};

struct derived : base {
    virtual void f() const {
        std::cout << "derived\n";
    }
};

template<typename T>
struct other_derived : base {
    virtual void f() const {
        std::cout << "other_derived\n";
    }
};

void test(derived d) {
    d.f();
    std::cout << "..\n";
}

void test(const base& b) {
    b.f();
    std::cout << "....\n";
}


int main() {
    test(derived{});
    test(base{});
    test(other_derived<int>{});
}