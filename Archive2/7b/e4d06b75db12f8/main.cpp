#include <iostream>

class B
{
    public:
    B(){std::cout<<"B Construcor" << std::endl;}
    virtual ~B(){std::cout<<"B Destructor" << std::endl;}
    virtual int shift(int n=2) const {return n << 2;}
};

class D : public B
{
    public:
    D(){std::cout<<"D Construcor" << std::endl;}
    virtual ~D(){std::cout<<"D Destructor" << std::endl;}
    virtual int shift(int n=3) const {return n << 3;}    
};

int main()
{
    const D d;
    const B* b = &d;
    
    std::cout << d.shift() << std::endl;
    std::cout << b->shift() << std::endl;
    
    return 0;
}