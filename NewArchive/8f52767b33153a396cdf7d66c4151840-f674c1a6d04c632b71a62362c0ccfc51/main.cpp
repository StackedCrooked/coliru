#include <iostream>

class A {
    public:
    int z;
    A(int y){z = y;}
};


class B {
    public:
    int x;
    A ob = 5; // Try this!
};


int main(){
    B b;
    std::cout << b.ob.z;
}