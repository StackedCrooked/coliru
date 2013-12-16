#include <limits>
#include <iostream>

struct Base {
    virtual void check() = 0;
    template<typename T> T* IsDerivedFrom() {
        try {
            check();
        } catch(T* p) {
            return p;
        } catch(...) {
            return nullptr;
        }
        return nullptr;
    }
};

template<typename T> struct Derived : public Base {
    Derived(T obj) : t(obj) {}
    T t;
    void check() override final {
        throw &t;
    }
};

struct A { virtual ~A() {} virtual void print() = 0;};
struct B : public A { int x; B(int y) : x(y) {} void print() override final { std::cout << x; } };

int main() {
    Base* b = new Derived<B>(B(5));
    A* p = b->IsDerivedFrom<A>();
    p->print();
}