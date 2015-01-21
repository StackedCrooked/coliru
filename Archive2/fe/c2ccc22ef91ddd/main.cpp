#include <iostream>
#include <vector>

template <typename t>
struct bob{ 
public :
    virtual void foo() = 0;
    
};
template <typename t>
void bob<t>::foo()
{
        std::cout<<"base" << std::endl;
}

struct derived : public bob<int>{ 
public :
    void foo() { 
        bob::foo();
        std::cout<<"derived" << std::endl;}

};

int main()

{

    
    bob<int> *b = new derived;
    b->foo();
    
    //bob c;
}
