#include <iostream>

class Base1{
public:
    Base1(){}
    virtual ~Base1(){}
};

class D1:public Base1{

};

class D2:public Base1{

};

class Base2{
public:
    Base2(){}
    virtual ~Base2(){}
    virtual Base1 * fun() = 0;
};

class _D1 : public Base2{
public:
    D1* fun(){ std::cout << "_D1" << std::endl; return nullptr; }
};

class _D2 : public Base2{
public:
    D2* fun(){ std::cout << "_D2" << std::endl; return nullptr;  }
};

int main()
{
    Base2* b1 = new _D1;
    b1->fun();
    
    Base2* b2 = new _D2;
    b2->fun();
}
