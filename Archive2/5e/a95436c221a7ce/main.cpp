#include <iostream>
#include <map>

class A
{
public:
    virtual void configure() = 0;
};


class B : public A
{
private: 
    void configure() override;
};

void B::configure(){ std::cout << "B::configure()" << std::endl; }


int main ()
{
    A* a = new B;
    a->configure();
}