#include <iostream>
#include <memory>

struct base {
    virtual void print() const = 0;
};

template<typename T>
struct a : public base {
    T t;
    a() = default;
    a(T t): t(t) {}
    
    ~a() {
        std::cout << "Deleted!" << std::endl;
    }
    
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
std::unique_ptr<a<T>> make() {
    return std::unique_ptr<a<T>>{ new a<T>() };
}

int main() {
    f(make<int>()->set(10));
}