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

void test(std::initializer_list<base> l) {
    for(auto&& i : l) {
        i.f();
    }
}


int main() {
    test({ base{}, derived{}, other_derived<int>{}});
}