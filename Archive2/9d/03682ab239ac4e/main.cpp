#include <iostream>

struct A {
    int n;
};

struct P {
    A a;
    
    A* operator->() {
        return &a;
    }
};

int main()
{
    P p;
    p->n = 5;
    
    std::cout << p.operator->();
}
