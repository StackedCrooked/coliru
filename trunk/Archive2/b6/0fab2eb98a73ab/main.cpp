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
    /** ta metoda przejmuje wirtualność z nadklasy **/
    SubDerived& operator=(const Base& rhs)
    {   std::cout << "SubDerived::operator=(Base)\n\n";  return *this;   }
    
    virtual SubDerived& operator=(const Derived& rhs)
    {   std::cout << "SubDerived::operator=(Derived)\n\n";  return *this;   }
    
    SubDerived& operator=(const SubDerived& rhs)
    {   std::cout << "SubDerived::operator=(SubDerived)\n\n";  return *this;   }
};

// Final : SubDerived
struct Final : public SubDerived
{
    virtual SubDerived& operator=(const Base& rhs)
    {   std::cout << "Final::operator=(Base)\n\n";  return *this;   }
    /** zwracany typu Derived będzie niekowariantny z SubDerived w nadklasie **/
    /*Derived*/SubDerived& operator=(const Derived& rhs)
    {   std::cout << "Final::operator=(Derived)\n\n";  return *this;   }
    
    SubDerived& operator=(const SubDerived& rhs)
    {   std::cout << "Final::operator=(SubDerived)\n\n";  return *this;   }
};

// main
int main()
{
    Base base;
    Derived derived;
    SubDerived subderived;
    Final final;
    Base& baseRefDerived = derived;
    Base& baseRefSubDerived = subderived;
    Derived& derivedRefSubDerived = subderived;
    Derived& derivedRefFinal = final;
    SubDerived& subDerivedRefFinal = final;

    std::cout << "1) \"Base = Derived\"\n";
    base = derived;  // Base::operator=(Base)
    
    std::cout << "2) \"Derived = Derived\"\n";
    derived = derived; // Derived::operator=(Derived)
    
    /** Brane są pod uwagę definicje z Base a następnie ewentualne wywołania wirtualne **/
    std::cout << "3) \"Base&(Derived) = Derived\"\n";
    baseRefDerived = derived;  // Base::operator=(Base)
    
    std::cout << "---------------------------------------\n";
    std::cout << "4) \"Base&(SubDerived) = Derived\"\n";
    baseRefSubDerived = derived; // SubDerived::operator=(Base)
    
    std::cout << "5) \"Base&(SubDerived) = SubDerived\"\n";
    baseRefSubDerived = subderived; // SubDerived::operator=(Base)
    
    std::cout << "---------------------------------------\n";
    /** nie kompiluje się bo Derive nie ma definicji pasującej dla argumentu Base **/
//    std::cout << "6) \"Derived&(SubDerived) = Base\"\n";
//    derivedRefSubDerived = base; // 
    
    /** brak wywołania wirtualnego **/
    std::cout << "7) \"Derived&(SubDerived) = Derived\"\n";
    derivedRefSubDerived = derived; // Derived::operator=(Derived)
    
    std::cout << "8) \"Derived&(SubDerived) = SubDerived\"\n";
    derivedRefSubDerived = subderived; // Derived::operator=(Derived)
    
    std::cout << "---------------------------------------\n";
    std::cout << "9) \"SubDerived = SubDerived\"\n";
    subderived = subderived; // SubDerived::operator=(SubDerived)
    
    std::cout << "10)\"SubDerived = Derived\"\n";
    subderived = derived; // SubDerived::operator=(Derived)
    
    std::cout << "---------------------------------------\n";
    /** zadziała wirtualność z Base mimo iż nie ma jej w SubDerived **/
    std::cout << "11)\"SubDerived&(Final) = Base\"\n";
    subDerivedRefFinal = base; // Final::operator=(Base)
    
    /** brak wirtualności w Derived mimo iż pojawia się później w SubDerived **/
    std::cout << "12)\"Derived&(Final) = Derived\"\n";
    derivedRefFinal = derived; // Derived::operator=(Derived)
    
    std::cout << "13)\"SubDerived&(Final) = SubDerived\"\n";
    subDerivedRefFinal = subderived; // SubDerived::operator=(SubDerived)
    
    return 0;
}
