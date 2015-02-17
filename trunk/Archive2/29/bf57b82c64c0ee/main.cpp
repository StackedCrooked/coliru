#include <iostream>
using namespace std;



struct A{
    
    A(){cout<<"Construct A"<<endl;}
    virtual void f(){ cout << "A";}
    };
    
    
struct B : virtual public A{
    void f(){ cout << "B";}
    B(){cout<<"Construct B"<<endl;} 
    };
    
struct C: virtual public A{
    void f(){ cout << "C";}
    C(){cout<<"Construct C"<<endl;}
    };
    
struct D:  public B,   public C{
    
    D(){cout<<"Construct D"<<endl;}
    };



int main(){
    D* d = new D();
    delete d;
    d->B::f();
    
}

