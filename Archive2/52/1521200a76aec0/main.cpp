#include <iostream>
 
class A
{
public:
    int i;
 
    A ( int i ) : i ( i ) {}
 
    virtual ~A()
    {
        std::cout << "~a" << i << std::endl;
    }
};

class B: public A
{
public:    
    B (int i) : A(i){}
    
    ~B()
    {
        std::cout << "~b" << i << std::endl;
    }
};
 
int main()
{
    A* p = new B(1);
    delete p; // calls the destructor of a3
}