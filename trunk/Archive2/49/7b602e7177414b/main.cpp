#include <iostream>

class Base {
protected:
    using fp_t = int(*)(Base*);
    fp_t fp;
    Base( fp_t p ) : fp( p ) {}     
public:
    int foo() { return (*fp)(this); }
};

class Derived : public Base {
    static int sfoo(Base* b) { return static_cast<Derived*>(b)->foo(); }
    int foo() { return 42; }
public:
    Derived() : Base(&sfoo) {}
};

class Derived1 : public Base {
    static int sfoo(Base* b) { return static_cast<Derived1*>(b)->foo(); }
    int foo() { return 1; }
public:
    Derived1() : Base(&sfoo) {}
};

int main()
{
    Derived d;
    Base* b = &d;
    std::cout << b->foo() << std::endl;
}
