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
    std::vector<B *> myVector{new B, new D, new D2, new B, new D2, new B, new D, new D, new D2, new B};
    
    std::sort( myVector.begin(), myVector.end(),
        [](const B* p1, const B* p2)
        {
            return
                std::type_index(typeid(*p1)) <
                std::type_index(typeid(*p2));
        }
    );
    
    for (auto p : myVector) {
        p->foo();
    }
}