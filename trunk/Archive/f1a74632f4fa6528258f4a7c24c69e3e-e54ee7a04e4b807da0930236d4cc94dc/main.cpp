#include <iostream>

struct Base
{
    float padding;
    std::string value;
    Base() : value("base")
    {
    }
    void member()
    {
        std::cout << value << std::endl;
    }
};

struct Derived : Base
{
    double padding;
    std::string value;
    Derived() : value("derived")
    {
    }
    void member()
    {
        std::cout << value << std::endl;
    }
};

typedef void (Base::*BaseMember)();
typedef void (Derived::*DerivedMember)();

int main()
{
    DerivedMember baseMember = &Base::member; // no static_cast required
    BaseMember derivedMember = static_cast<BaseMember>(&Derived::member);
    
  	Derived d;
    (d.*baseMember)(); // output: "base"
      
    Base* b = &d;
    (b->*derivedMember)(); // output: "derived"
}
