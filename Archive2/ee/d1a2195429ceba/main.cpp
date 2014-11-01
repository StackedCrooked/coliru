#include <iostream>

struct X {
    X(){ };
    X(const X&, int i);
};

X::X(const X& x, int i = 7) { std::cout << "ctor" << std::endl; }

X x;

X z = x;

int main()
{ 
    
}

