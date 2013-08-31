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

typedef void (Base::*P)();

int main()
{
    P baseMember = &Base::member;
    P derivedMember = static_cast<P>(&Derived::member);
    
  	Derived d;
    (d.*baseMember)(); // output: "base: 0"
    (d.*derivedMember)(); // output: "derived: 1"
      
    Base* b = &d;
    (b->*baseMember)(); // output: "base: 0"
    (b->*derivedMember)(); // output: "derived: 1"
}
