#include <iostream>
#define FUN(CLASS) std::cout << #CLASS << "::" << __FUNCTION__ << "()\n"

class Animal
{
public:
    virtual void eat() { FUN(Animal); }
    long int type[10];
};
 
class Mammal : public virtual Animal
{
public:
    virtual void eat() { FUN(Mammal); }
    long int type[100];
};
 
class Winged : public virtual Animal
{
public:
//    virtual void eat() { FUN(Winged); }
};

class Bat : public virtual Mammal, public  Winged
{
public:
//    using Animal::eat;
//    virtual void eat() { FUN(Bat); }
//    void eat() { Animal::eat(); }
};

class Human : public virtual Mammal
{
public:  
    virtual void eat() { FUN(Human); }
};

class BatMan : public Human, public Bat
{
public:  
    virtual void eat() { FUN(BatMan); }
};


int main()
{
    std::cout << "Animal: " << sizeof(Animal)/8 << "\n";
    std::cout << "Mammal: " << sizeof(Mammal)/8 << "\n";
    std::cout << "Bat:    " << sizeof(Bat)/8 << "\n";
    std::cout << "BatMan: " << sizeof(BatMan)/8 << "\n";
    return 0;
}
