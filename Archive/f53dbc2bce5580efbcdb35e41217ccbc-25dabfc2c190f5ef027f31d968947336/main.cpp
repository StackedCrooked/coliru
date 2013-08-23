struct Base {
    virtual int foo(int i = 5) const {
        return i;
    }
};

struct Derived : Base {
    virtual int foo(int i = 10) const {
        return Base::foo(i);
    }
};


#include <iostream>

int main()
{
    Derived const& d = Derived();
    Base const&    b = d;
    std::cout << d.foo() << ", " << b.foo() << std::endl;
}
