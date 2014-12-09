#include <iostream>
#include <memory>
#include "boost/variant.hpp"

struct Derived1 {
    void foo1(){
        std::cout << "D1" << std::endl;
    }
};

struct Derived2 {
    void foo2(){
        std::cout << "D2" << std::endl;
    }
};

class some_visitor : public boost::static_visitor<void> {
public:
    void operator()(Derived1& x) const {
        x.foo1();
    }
    
    void operator()(Derived2& x) const {
        x.foo2();
    }
};

int main() {
    bool condition = false;
    boost::variant<Derived1, Derived2> x;
    boost::apply_visitor(some_visitor(), x);
    
    if (!condition)  x = Derived2();
    boost::apply_visitor(some_visitor(), x);
}