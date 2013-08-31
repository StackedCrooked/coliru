#include <iostream>
#include <memory>

class A
{
public:
    virtual void Do() = 0;
};

class B : public A
{
public:
    virtual void Do()
    {
        std::cout << "doiing" << std::endl;
    }
};


int main()
{
    std::unique_ptr<B> p( new B() );
    p->Do();
    
    return 0;
}
