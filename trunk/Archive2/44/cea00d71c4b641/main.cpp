#include <iostream>

class Setting
{
public:
    Setting(){
     f1();
     f2();
     //...
    }
    virtual void f1() { std::cout << "B::f1" << std::endl; }
     virtual void f2() { std::cout << "B::f2" << std::endl; }
protected:
    void init()
    {
        f1();
        f2();
    }
};

class Setting2:public Setting
{
public:
    Setting2(){
    //duplicating same stuffs
    init();
     //...
    }
    virtual void f1() { std::cout << "C::f1" << std::endl; }
     virtual void f2() { std::cout << "C::f2" << std::endl; }
};

int main()
{
    Setting2 set;
}