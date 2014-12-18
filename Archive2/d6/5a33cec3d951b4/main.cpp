#include <iostream>
struct B {
    virtual void f(){ std::cout << "B" << std::endl;}
}; 

struct D /* final_overrider*/ : B 
{
    void f(){ std::cout << "D" << std::endl;} /* must override, we are the final overrider*/
}; 

struct J :  B
{
    void f(){ std::cout <<"J" << std::endl;}        
};
struct E : J, D {
    
    //void f(){ std::cout << "E"<< std::endl;}
    
}; 

int main()
{
   J* foo = new E;
   foo->f();
    
   D* bar = new E; 
   bar->f();
}