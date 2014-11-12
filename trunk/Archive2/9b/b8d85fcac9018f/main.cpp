#include <iostream>
#include <memory>
// Base.h
class Derived;
class Base
{
protected:
    typedef std::shared_ptr<Derived> DerivedPtr;
public:
    void doSomething(DerivedPtr aDerived);
protected:
    Base() = default;
};


// Derived.h
class Derived : public std::enable_shared_from_this<Derived>, public Base
{
public:
    Derived():std::enable_shared_from_this<Derived>(), Base(){}
    void doSomething(DerivedPtr aDerived)
    {
        Base::doSomething(aDerived);
    }
};

void Base::doSomething(DerivedPtr aDerived)
{
    DerivedPtr lDerived = reinterpret_cast<Derived*>(this)->shared_from_this();
}

int main()
{
    std::shared_ptr<Derived> derived = std::make_shared<Derived>();
    std::shared_ptr<Base> other_derived = std::make_shared<Derived>();
    
    other_derived->doSomething(derived);
}