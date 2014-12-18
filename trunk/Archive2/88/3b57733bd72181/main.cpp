#include <iostream>

class foo
{
public:
    foo();
    foo(foo const &);
    
    ~foo();
    
    foo & operator=(foo const &);
};

foo::foo() { std::cout << "ctor" << std::endl; }

foo::foo(foo const & ) { std::cout << "copy ctor" << std::endl; }

foo::~foo() { std::cout << "dtor" << std::endl; }

foo & foo::operator=(foo const &)
{
    std::cout << "copy assign" << std::endl;
    return *this;
}

foo make_foo()
{
    foo f;
    return f;
}

int main()
{
    foo x = make_foo();
    
    return 0;
}