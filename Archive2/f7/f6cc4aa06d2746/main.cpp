#include <iostream>

struct LOUD {
    LOUD() {std::cout << "DEF CTOR\n";}
    ~LOUD() {std::cout << "DTOR\n";}
    LOUD(const LOUD&) {std::cout << "CPY CTOR\n";}
    LOUD(LOUD&&) {std::cout << "MOV CTOR\n";}
    LOUD& operator=(const LOUD&) {std::cout << "CPY ASN\n"; return *this;}
    LOUD& operator=(LOUD&&) {std::cout << "MOV ASN\n"; return *this;}
};

struct Base {
    LOUD l;
};

struct Derived : Base {
    Derived() = default;
    Derived(Base&& b) : Base(std::move(b)) {}
};

int main()
{
    std::cout << "Base a;\n";
    Base a;
    std::cout << "Derived b\n";
    Derived b;
    std::cout << "Derived c=b\n";
    Derived c=b;
    std::cout << "Derived d=move(b)\n";
    Derived d=std::move(b);
    std::cout << "Derived e=move(a)\n";
    Derived e=std::move(a);
    std::cout << "return 0\n";    
    return 0;
}