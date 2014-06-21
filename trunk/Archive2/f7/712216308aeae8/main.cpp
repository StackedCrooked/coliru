#include <iostream>
// Base
struct Base
{
    virtual Base& operator=(const Base& rhs)
    {   std::cout << "Base::operator=(Base)\n\n";  return *this;   }
};

// Derived : Base
struct Derived : public Base
{     /** dla tego typu operator z klasy bazowej nie będzie widoczny **/
//    virtual Derived& operator=(const Base& rhs)
//    {   std::cout << "Derived::operator=(Base)\n\n";  return *this;   }
    /** bez virtual przy referencjach trzymających podklasy ich nadpisane operatory nie będa wywołane **/
    /*virtual*/ Derived& operator=(const Derived& rhs)
    {   std::cout << "Derived::operator=(Derived)\n\n";  return *this;   }
};

// SubDerived : Derived
struct SubDerived : public Derived
{
    SubDerived& operator=(const Base& rhs)
    {   std::cout << "SubDerived::operator=(Base)\n\n";  return *this;   }
    
    virtual SubDerived& operator=(const Derived& rhs)
    {   std::cout << "SubDerived::operator=(Derived)\n\n";  return *this;   }
    
    virtual SubDerived& operator=(const SubDerived& rhs)
    {   std::cout << "SubDerived::operator=(SubDerived)\n\n";  return *this;   }
};

// main
int main()
{
    Base base;
    Derived derived;
    SubDerived subderived;
    Base& baseRefDerived = derived;
    Base& baseRefSubDerived = subderived;
    Derived& derivedRefSubDerived = subderived;

    std::cout << "\"Base = Derived\"\n";
    base = derived;  // Base::operator=(Base)
    
    std::cout << "\"Derived = Derived\"\n";
    derived = derived; // Derived::operator=(Derived)
    
    /** Brane są pod uwagę definicje z Base a następnie ewentualne wywołania wirtualne **/
    std::cout << "\"Base&(Derived) = Derived\"\n";
    baseRefDerived = derived;  // Derived::operator=(Base)
    
    std::cout << "---------------------------------------\n";
    std::cout << "\"Base&(SubDerived) = Derived\"\n";
    baseRefSubDerived = derived; // SubDerived::operator=(Base)
    
    std::cout << "\"Base&(SubDerived) = SubDerived\"\n";
    baseRefSubDerived = subderived; // SubDerived::operator=(Base)
    
    std::cout << "---------------------------------------\n";
    /** nie kompiluje się bo Derive nie ma definicji pasującej dla argumentu Base **/
//    std::cout << "\"Derived&(SubDerived) = Base\"\n";
//    derivedRefSubDerived = base; // 
    
    /** brak wywołania wirtualnego **/
    std::cout << "\"Derived&(SubDerived) = Derived\"\n";
    derivedRefSubDerived = derived; // Derived::operator=(Derived)
    
    std::cout << "\"Derived&(SubDerived) = SubDerived\"\n";
    derivedRefSubDerived = subderived; // Derived::operator=(Derived)
    
    std::cout << "---------------------------------------\n";
    std::cout << "\"SubDerived = SubDerived\"\n";
    subderived = subderived; // SubDerived::operator=(SubDerived)
    
    std::cout << "\"SubDerived = Derived\"\n";
    subderived = derived; // SubDerived::operator=(Derived)
    
    return 0;
}
