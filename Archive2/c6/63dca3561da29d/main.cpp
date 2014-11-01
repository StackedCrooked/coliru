#include <iostream>

struct X {
    X(){ };
    X(const X&, int i = 6);
};

X::X(const X& x, int i) { std::cout << "ctor" << std::endl; }

X x;

X z = x;

int main()
{ 
    
}

