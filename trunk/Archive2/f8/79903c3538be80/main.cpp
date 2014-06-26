#include <iostream>
class Base
{
    public:
        virtual ~Base() {}
        virtual const Base& fun() const 
        {
            std::cout<<"fun() in Base\n";
            return *this;
        }
};
class Derived : public Base
{
    public:
        virtual ~Derived() {}
        const Derived& fun() const
        {
            std::cout<<"fun() in Derived\n";
            return *this;
        }
};
int main()
{
    Base* p=new Derived();
    p->fun();
    delete p;
    return 0;
}