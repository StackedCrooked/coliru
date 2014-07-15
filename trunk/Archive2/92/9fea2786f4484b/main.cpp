#include <iostream>

class Base;

class Helper
{
    public:
        void f(Base* base);
};

class Base
{
    int i, j;
    friend class Helper;
protected:
    Base() {}
};

class Derived : public Base
{
public:
    void f();
private:
    Helper helper;
};

void Helper::f(Base* base)
{
    base->i = 10; base->j = 5;
    std::cout << "Help !" ;
}

void Derived::f()
{
    helper.f(this);
}

int main(int argc, char** argv) {
  Derived d;
  d.f(); 
  return 0;
}