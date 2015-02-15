#include <iostream>
#include <memory>
#include <cassert>

class A
{
public:
    virtual A* clone() = 0;
};

template <typename T>
struct Cloner : A {
    using A::A; // For constructors
    virtual A* clone() override {return new T;}
};

class B : public Cloner<B>
{
};

int main()
{
    std::unique_ptr<A> p = std::make_unique<B>();
    assert( dynamic_cast<B*>(p->clone()) );
}