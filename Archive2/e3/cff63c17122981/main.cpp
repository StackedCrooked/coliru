#include<iostream>

class Loner;

class Base
{
    friend Loner;
private:
    virtual void test(){std::cout << "Base" << std::endl;}
};

class Derived : public Base
{
private:
    virtual void test(){std::cout << "Derived" << std::endl;}
};

class Loner
{
public:
    void test(Base *base){base->test();}
};

int main()
{
    Loner loner;
    Derived derived;
    loner.test(&derived);
}
