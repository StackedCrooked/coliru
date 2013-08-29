#include <iostream>

struct Base
{
    int value;
    Base() : value(0)
    {
    }
    void member()
    {
        std::cout << "base: " << value << std::endl;
    }
};

struct Derived : Base
{
    int value;
    Derived() : value(1)
    {
    }
    void member()
    {
        std::cout << "derived: " << value << std::endl;
    }
};

typedef void (Base::*BaseMember)();
typedef void (Derived::*DerivedMember)();

int main()
{
    DerivedMember baseMember = &Base::member; // no static_cast required
    BaseMember derivedMember = static_cast<BaseMember>(&Derived::member);
    
  	Derived d;
    (d.*baseMember)(); // output: "base: 0"
      
    Base* b = &d;
    (b->*derivedMember)(); // output: "derived: 1"
}
