#include <iostream>
using namespace std;

struct A
{
    virtual void f(){ cout << __PRETTY_FUNCTION__ << endl;}
    void g(){cout << __PRETTY_FUNCTION__ << endl;}
};    
struct B : virtual A
{
    virtual void f() override{cout << __PRETTY_FUNCTION__ << endl;}
    void g(){cout << __PRETTY_FUNCTION__ << endl;}
};     
struct C :  virtual A
{   
};    
struct D: B, C
{    
};

int main()
{
    D d;
    d.f(); //B::f is called
    d.g(); //B::g is called
}