#include <iostream>
#include <vector>
struct bob{ 
public :
    void foo() { std::cout<<"base" << std::endl;}

};

struct derived : public bob{ 
public :
    void foo() { std::cout<<"derived" << std::endl;}

};

int main()

{

    
    bob *b = new derived;
    b->foo();
}
