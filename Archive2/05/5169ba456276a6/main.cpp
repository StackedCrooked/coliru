#include <iostream>
#include <vector>

template <typename t>
struct bob{ 
public :
    virtual void foo() = 0;
    
};
template <typename t>
void bob::foo()
{
        std::cout<<"base" << std::endl;
}

struct derived : public bob{ 
public :
    void foo() { 
        bob::foo();
        std::cout<<"derived" << std::endl;}

};

int main()

{

    
    bob *b = new derived;
    b->foo();
    
    //bob c;
}
