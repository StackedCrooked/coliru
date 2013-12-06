#include <iostream>

struct A {
    struct B {
        int first = 1;
        int second = 2;
        
        B* operator -> () { return this; }        
    };
    
    B operator -> () const { return {}; }
};

int main() {
    A a;
    std::cout << a->first << '\n';
}
