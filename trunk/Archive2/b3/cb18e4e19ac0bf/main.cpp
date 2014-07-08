#include <memory>
#include <iostream>
#include <cassert>

struct Foo {
    Foo(int id) : id(id) {}
    ~Foo() { std::cout << __PRETTY_FUNCTION__ << ": " << id << std::endl; }
    int id;
    
    static void aFunction(std::auto_ptr<Foo> x)
    {
    }
};


int main() {
    {
        std::auto_ptr<Foo> pf1(new Foo(1));
        std::auto_ptr<Foo> pf2(new Foo(2));
    }
    std::auto_ptr<Foo> pf3(new Foo(3));
    std::auto_ptr<Foo> pf4 = pf3;
    assert(pf3.get() == 0);
    Foo f1(1);
    std::auto_ptr<Foo> pf6(new Foo(6));
    Foo::aFunction(pf6);
    std::auto_ptr<Foo> pf5(new int);
    std::cout << pf5.get();
    Foo::aFunction(pf4);
}