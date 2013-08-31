#include <iostream>
#include <exception>
#include <stdexcept>
#include <functional>

class Base {
    int x;
    
    Base(Base&);
    Base& operator=(Base&);
public:
    Base() : x(0) { }
    Base(int _x) :
        x(_x)
    {
    }
    
    void construct(int _x) {
        x = _x;
    }

    Base& operator= (int _x)
    { 
        x = _x;
        return *this;
    }
};

class Derived : public Base
{
};

int main() {
   
   Derived d;
   //d = 5;  -- compilation error
   d.construct(5);
   
}