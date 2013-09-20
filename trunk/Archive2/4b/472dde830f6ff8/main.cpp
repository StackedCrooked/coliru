#include <iostream>
#include <string>
#include <vector>


class B // Base Class
{
private:
    virtual void f1(){ std::cout << "B::f1" << std::endl; }
    
public:
    virtual void f2(){ std::cout << "B::f2" << std::endl; }
};


// Derived Class
class D : public B   
{
// switch access specifier
public:  // was private
    virtual void f1(){ std::cout << "public D::f1" << std::endl; }
    
private: // was public
    virtual void f2(){ std::cout << "private D::f2" << std::endl; }
};


//Two Times Derived Class
class DD : public D
{
// switch access specifier again
private:
    virtual void f1(){ std::cout << "private DD::f1" << std::endl; }
    
public:
    virtual void f2(){ std::cout << "public DD::f2" << std::endl; }
};


int main()
{
    B b;
    D d;
    DD dd;
    
    //+++++ Test D Class
    B &rD = d;      //B class reference to D object

    //rD.f1();      // does not compile, is private in B
    rD.f2();        // is public in B, private in D

    d.f1();         // is private in B, public in D
    //d.f2();       // does not compile, is private in D
    //+++++ Test DD Class
    
    B &rDD = dd;    //B class reference to DD object    

    //rDD.f1();     // does not compile, is private in B
    rDD.f2();       // is public in B
    
    //dd.f1();      // does not compile, is private in DD
    dd.f2();        // is public in DD
}
