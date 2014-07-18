#include <initializer_list>
#include <functional>
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

typedef std::initializer_list<std::reference_wrapper<base> > L;
void test(L l) {
    for (auto&& i : l) {
        i.get().f();
    }
}


int main() {
    test(L{ base{}, derived{}, other_derived<int>{}});
}