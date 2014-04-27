#include <iostream>
#include <typeinfo>

struct Base1 {
    virtual void foo() = 0;
};

struct Base2 {
    Base2(const std::type_info& t) {
        std::cout << t.name() << '\n';
    }
};

struct Derived : Base1, Base2 {
    Derived() : Base2(typeid(*this)) {}
    void foo() {}
};

int main() {
    Derived();
}
