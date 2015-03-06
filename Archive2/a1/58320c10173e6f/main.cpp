#include <iostream>
#include <string>
#include <map>

struct Base
{

    virtual const bool operator<(const Base & other) const= 0;
    
    const bool operator>(const Base &other) const
    {
        return other < *this; // Pure Virtual function called!
    }
    virtual ~Base() {}

};


struct Derived : Base
{
    const bool operator<(const Base & other) const
    {
        const Derived& t = dynamic_cast<const Derived&>(other);
        return t < *this;
    }
};


int main()
{
    Derived z;
    Base* h= new Derived();
    delete h;
}
