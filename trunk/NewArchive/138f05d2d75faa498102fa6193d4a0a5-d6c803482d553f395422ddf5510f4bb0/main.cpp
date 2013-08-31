#include <iostream>

struct base {
    virtual void print() const = 0;
};

template<typename T>
struct a : public base {
    T t;
    a(T t): t(t) {}
    virtual void print() const {
        std::cout << t << '\n';
    }
};

void f(const base* b) {
    b->print();
}

int main() {
    a<int> some_a(10);
    f(&some_a);
    //^
}