#include <iostream>

struct A {};

struct B {
    B(A) {}
    
    bool operator==(B) const {
        return true;
    }    
};
    
int main()
{    
    A a;
    B b;
    a == b;
    
    return 0;
}