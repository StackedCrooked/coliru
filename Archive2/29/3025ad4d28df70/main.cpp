#include <algorithm>
#include <iostream>
#include <typeindex>
#include <typeinfo>
#include <vector>

struct B {
    virtual void foo() {std::cout << "B ";}    
};

struct D : B {
    virtual void foo() {std::cout << "D ";}
};

struct D2 : B {
    virtual void foo() {std::cout << "D2 ";}
};

int main() {
    std::vector<B *> v{new B, new D, new D2, new B, new D2, new B, new D, new D, new D2, new B};
    std::sort(begin(v), end(v), [](const B *a, const B *b) {return std::type_index(typeid(a)) < std::type_index(typeid(b));});
    
    for (auto p : v) {
        p->foo();
    }
}