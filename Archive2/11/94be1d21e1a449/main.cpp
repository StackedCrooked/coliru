#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>

class A {
public:
    virtual void A1()=0;
    virtual void A2()=0;
    virtual void A3()=0;
    virtual void AB1()=0;
    virtual void AB2()=0;    
    virtual void AB3()=0;    
    ~A(){}
};

class B {
public:
    virtual void B1()=0;
    virtual void B2()=0;
    virtual void AB1()=0;
    virtual void AB2()=0; 
    virtual void AB3()=0;        
    ~B(){}
};

class Global : public A , public B
{
public:
    using A::AB1;
    virtual void AB2() override =0; 
   
    ~Global(){}    
};

class Impl : public Global {
public:
    void A1() override { std::cout << __FUNCTION__ << std::endl; }
    void A2() override { std::cout << __FUNCTION__ << std::endl; }
    void A3() override { std::cout << __FUNCTION__ << std::endl; }
    
    void B1() override { std::cout << __FUNCTION__ << std::endl; }
    void B2() override { std::cout << __FUNCTION__ << std::endl; }
    
    void AB1() override { std::cout << __FUNCTION__ << std::endl; }
    void AB2() override { std::cout << __FUNCTION__ << std::endl; }
    void AB3() override { std::cout << __FUNCTION__ << std::endl; }
};


int main (int argc, char* argv[])
{
    Impl impl;
    
    Global& global = impl;
    A& a = impl;
    B& b = impl;
    
    impl.A1();
    impl.B1();
    impl.AB1();
    impl.AB2();
    impl.AB3();
    
    std::cout << std::endl;
    
    a.A1();
    b.B1();
    
    std::cout << std::endl;
    
    a.AB1();
    a.AB2();
    a.AB3();
    
    std::cout << std::endl;
    
    b.AB1();
    b.AB2();
    b.AB3();

    std::cout << std::endl;

    global.A1();
    global.B1();
    global.AB1();
    global.AB2();
    // global.AB3(); // Does not compile

  return 0;
}