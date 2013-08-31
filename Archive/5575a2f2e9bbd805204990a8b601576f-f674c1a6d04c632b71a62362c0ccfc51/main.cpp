#include <iostream>
#include <string>
#include <vector>

#include <iterator> 
#include <algorithm> 
#include <functional> 

#include <exception> 
/******************************************************/
class base{ virtual void dummy() {} };
class derived : public base { };
/******************************************************/
class pro
{
    public:
    //pro() {}
	virtual ~pro();
	//int a;
	//char b;
	//int c;
};

class con
{
    struct node
    {
        int data;
        int rest;
    };
    
    public:
    con() {}
};
/******************************************************/
class A{
  public:
  A(){
    std::cout << "In A\n";
  }
};

class vB:virtual public A{
  public:
  vB(){
    std::cout << "In vB\n";
  }
};

class nvB: public A{
  public:
  nvB(){
    std::cout << "In nvB\n";
  }
};

class D1: public vB, public nvB{// A vB A nvB D1 , first base virtual
  public:
  D1(){
    std::cout << "In D1\n";
  }
};

class D2: public nvB, public vB{// A A nvB vB D2 , first base not virtual
  public:
  D2(){
    std::cout << "In D2\n";
  }
};
/******************************************************/
class derbase {
    public:
    virtual void func(int i,int j=10)
    {
        std::cout<<"base func"<<std::endl;
    }
};

class der:public derbase
{
    public:
    void func(int i,int j=5)
    {
        std::cout<<"der "<<j<<" func"<<std::endl;
    }
};
/******************************************************/
struct baseS 
{
    int val ; 
    baseS() : val(100) {} 
    virtual int foo() { return val ; } 
}; 

struct derivedS : public baseS 
{
    double val ;
    derivedS() : val(200.2) {} 
    virtual int foo() { return val ; } 
} ; 
/******************************************************/
int main()
{
    base* pb ;
    derived* pd; derived d;
    
    pb = dynamic_cast<base*>(&d);
    
    pd = dynamic_cast<derived*>(pb);
    /******************************************************/
    std::cout << sizeof(A) << std::endl;
    
    con c;
    std::cout << sizeof(c) << std::endl;
    /******************************************************/
    D1 d1;
    D2 d2;
    /******************************************************/
    der dd;
    derbase *bb = new der();
    bb->func(9);
    dd.func(9,1);
    dd.func(9);
    bb->func(9,2);
    /******************************************************/
    int count = 0; 
    for(int i=0; i < 10; ++i) 
        count = count++; 
    std::cout << count; 
    /******************************************************/
    std::vector<baseS*> vec( 3 ) ;
    derivedS derived ;
    std::fill( vec.begin(), vec.end(), &derived ) ;
    std::transform( vec.begin(), vec.end(), std::ostream_iterator<int>( std::cout, "+" ), std::mem_fun( &baseS::foo ) ) ; 
    /******************************************************/
    return 0;
}