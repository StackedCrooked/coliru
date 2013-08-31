struct foo
{
    virtual ~foo() {}
};

struct bar
{
    virtual ~bar() {}
};

struct foobar : foo, bar
{
};

#include <iostream>

int main()
{
    foobar f;
    bar* p = &f;
    
    std::cout << "implicit cast from foobar* to void*: " << &f << std::endl;
    std::cout << "implicit cast from bar* to void*: " << p << std::endl;
    std::cout << "dynamic cast from bar* to void*: " << dynamic_cast<void*>(p) << std::endl;
}
