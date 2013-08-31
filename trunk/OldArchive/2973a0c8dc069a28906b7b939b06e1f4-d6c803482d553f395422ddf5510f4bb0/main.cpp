#include <iostream>

struct base {
    virtual void print() const = 0;
};

template<typename T>
struct a : public base {
    T t;
    a() = default;
    a(T t): t(t) {}
    virtual void print() const {
        std::cout << t << '\n';
    }
    a* set(T stuff) {
        t = stuff;
        return this;
    }
};

void f(const base* b) {
    b->print();
}

template<typename T>
a<T>* make() {
    return new a<T>();
}

int main() {
    f(make<int>()->set(10));
}