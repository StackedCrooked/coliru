#include <iostream>
#include <sstream>
#include <memory>

struct A
{
    virtual int operator()(int x) const noexcept { return 0 + x; }
    int operator()() const noexcept { return this->operator()(0); }
    virtual ~A() {}
};
struct B : public A
{
    int operator()(int x) const noexcept { return 1 + x; }
};
struct C : public A
{
    int operator()(int x) const noexcept { return 2 + x; }
};

int main (int argc, char *argv [])
{
    std::shared_ptr<const A> a ( new A );
    std::shared_ptr<const A> b ( new B );
    std::shared_ptr<const A> c ( new C );
    std::cout << (*a)() << (*b)() << (*c)() << std::endl;
    return 0; 
}