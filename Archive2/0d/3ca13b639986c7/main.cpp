//based on:
//  http://en.cppreference.com/w/cpp/language/ebo

#include <cassert>
 
struct Base {}; // empty class
 
struct Derived1 : Base {
    int i;
};

struct Base2 {};

struct Derived2 : Base, Base2 {
    int i;
};

 
int main()
{
    // the size of any object of empty class type is at least 1
    assert(sizeof(Base) == 1);
 
    // empty base optimization applies
    assert(sizeof(Derived1) == sizeof(int));
    
    // empty base optimization applies
    assert(sizeof(Derived2) == sizeof(int));
}