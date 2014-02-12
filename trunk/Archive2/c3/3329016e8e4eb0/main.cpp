#ifndef MYHEADERFILE
#define MYHEADERFILE

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

#endif