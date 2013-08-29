#include <iostream>

struct Base
{
    float padding;
    std::string value;
    Base() : value("base")
    {
    }
    void baseMember()
    {
        std::cout << value << std::endl;
    }
};

struct Derived : Base
{
    std::string value;
    Derived() : value("derived")
    {
    }
    void derivedMember()
    {
        std::cout << value << std::endl;
    }
};

typedef void (Base::*BaseMember)();
typedef void (Derived::*DerivedMember)();

int main()
{
    DerivedMember baseMember = &Base::baseMember; // no static_cast required
    BaseMember derivedMember = static_cast<BaseMember>(&Derived::derivedMember);
    
  	Derived d;
    (d.*baseMember)(); // output: "base"
      
    Base& b = d;
    (b.*derivedMember)(); // output: "derived"
    
    Base bad;
    //(bad.*derivedMember)(); // output: undefined
}
