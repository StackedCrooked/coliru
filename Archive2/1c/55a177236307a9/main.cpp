#include <stdio.h>
#include <typeinfo>

struct Base1 {
    virtual void foo() = 0;
};

struct Base2 {
    Base2(const std::type_info& t) {
        printf("%s\n", t.name());
    }
};

struct Derived : Base1, Base2 {
    Derived() : Base2(typeid(*this)) {}
    void foo() {}
};

int main() {
    Derived();
}
