#include <iostream>
#include <memory>
#include <boost/scoped_ptr.hpp>
#include <boost/any.hpp>
#include <boost/variant.hpp>

#include <functional>

struct A {
    A(int value) : value(value) {}
    
    std::function<void(A*)> factory() {
        return [](A* a) { std::cout << a->value; }; 
    }    

private:
    int value;    
};    

int main() {
    A a(1);
    auto f = a.factory();
    f(&a);
    
    return 0;
}

