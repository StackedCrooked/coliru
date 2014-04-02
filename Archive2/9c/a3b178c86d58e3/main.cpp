#include <iostream>
#include <memory>

template < typename T > 
std::unique_ptr<T> make_unique() { 
    return std::unique_ptr<T>( new T{} ); 
}

struct A { 
    ~A() { std::cout << "~A\n"; } 
};

struct B : public A {
    ~B() { std::cout << "~B\n"; }
};

struct VA {
    virtual ~VA() { std::cout << "~VA\n"; }
};

struct VB : public VA {
    ~VB() { std::cout << "~VB\n"; }
};

int main() {
    std::unique_ptr<A> i1 { new B };
    std::unique_ptr<A> i2 = make_unique<B>();
    
    std::unique_ptr<VA> i3 { new VB };
    std::unique_ptr<VA> i4 = make_unique<VB>();
}
