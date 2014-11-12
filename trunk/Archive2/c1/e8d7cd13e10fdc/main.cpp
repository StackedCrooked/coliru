#include <cassert>
#include <iostream>
#include <vector>
#include <future>

class Parent
{

};

class Child : public Parent
{
public:
    void m();
};



void Child::m()
{
    Parent* p1 = (Parent*)this;
    Parent* p2 = static_cast<Parent*>(this);
}

int main() {
    
    return 0;
}