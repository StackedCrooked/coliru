#include <cassert>
#include <iostream>
 
struct Base {}; // empty class
 
struct Derived1 : Base {
public:    
    int i;
};

int main()
{
    // the size of any object of empty class type is at least 1
    assert(sizeof(Base) == 1);
 
    // empty base optimization applies
    assert(sizeof(Derived1) == sizeof(int));
    
    Base objBase;
    Derived1 objDerived;
    objDerived.i = 42;
    Base& refToobjDerived = objDerived;
    
    char buf[sizeof(Base)]; // 1
    
    std::memcpy(buf, &objBase, sizeof(Base)); // copy objBase to buf
    // might do something with buf..
    std::memcpy(&refToobjDerived, buf, sizeof(Base)); // EBO! I'm overwriting the int's value!
    
    std::cout << objDerived.i; // Screwed
}