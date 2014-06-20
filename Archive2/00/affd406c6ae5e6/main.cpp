#include <iostream>
// Base
struct Base
{
    friend bool operator==(const Base& lhs, const Base& rhs)
    {   std::cout << "operator==(Base, Base)\n\n";  return true;   }
};

// Derived : Base
struct Derived : public Base
{
    friend bool operator==(const Derived& lhs, const Derived& rhs)
    {   std::cout << "operator==(Derived, Derived)\n\n";  return true;   }
};

// SubDerived : Derived
struct SubDerived : public Derived
{
    friend bool operator==(const SubDerived& lhs, const SubDerived& rhs)
    {   std::cout << "operator==(SubDerived, SubDerived)\n\n";  return true;   }
};


// main
int main()
{
    Base base;
    Derived derived;
    Base& baseRefDerived = derived;
    SubDerived subderived;

    std::cout << "\"Base == Derived\"\n";
    base == derived;  // referencja pochodnego Derived rzutowana na referencję klasy bazowej
    
    std::cout << "\"Derived == Derived\"\n";
    derived == derived;
    
    std::cout << "\"Base& == Derived\"\n";
    baseRefDerived == derived;  // mimo iż pod referencją Base jest obiekt Derived to rzutowany jest druga referencja Derived na referencję klasy bazowej
    
    std::cout << "\"SubDerived == Derived\"\n";
    subderived == derived;  // rzutowanie jest do najbliższego typu bazowego - nie do jawyższej klasy bazowej
    
    return 0;
}
