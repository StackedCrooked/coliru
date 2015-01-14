#include <iostream>

struct Base
{
    virtual void print() const
    {
        std::cout << "Base\n";
    }
    virtual Base* clone() const
    {
        return new Base(*this);
    }
    virtual ~Base() = default;
};

struct Derived: Base
{ 
    virtual void print() const override
    {
        std::cout << "Derived\n";
    }
    virtual Derived* clone() const override
    {
        return new Derived(*this);
    }
};

int main()
{
    Base* p  = new Derived;
    Base* px = p->clone();
    delete p;
    px->print();
    delete px;
}
