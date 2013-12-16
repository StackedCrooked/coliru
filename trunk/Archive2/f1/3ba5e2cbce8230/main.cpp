struct ICloneable
{
    virtual const char* whoami() const = 0;
    virtual ICloneable* clone() const = 0;
};

#include <string>

struct A : ICloneable
{
    virtual const char* whoami() const { return "struct A"; }
    virtual ICloneable* clone() const { return new A; }
};

struct B : ICloneable
{
    virtual const char* whoami() const { return "struct B"; }
    virtual ICloneable* clone() const { return new B; }
};

#include <iostream>
#include <typeinfo>

int main()
{
    A a;
    B b;

    ICloneable* aclone = a.clone();
    ICloneable* bclone = b.clone();

    std::cout << typeid(*aclone).name() << "\n";
    std::cout << typeid(*bclone).name() << "\n";
}
