#include <iostream>

template<class T> struct Base {
    typedef T type;
    static const int n = 3;
    virtual int f() { return n; }
};

// doesn't compile!
template<class T> struct Derived : Base<T> {
    T field; // The compiler doesn't know T yet!
//    int f() override { return this->n; } // the compiler doesn't know n yet!
    int bar() { return this->f(); }
};

int main()
{
    Derived<int> d;
    
    std::cout << d.bar() << '\n';
}
