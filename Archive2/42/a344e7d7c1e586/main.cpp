#include <iostream>
#include <iomanip>

struct base
{
    base()  { std::cout << "base::base()" << std::endl; }
    ~base() { std::cout << "base::~base()" << std::endl; }
    
    virtual void run() {}
};

struct derived : public base
{
    derived()  { std::cout << "derived::derived()" << std::endl; }
    ~derived() { std::cout << "derived::~derived()" << std::endl; }  
};

int main()
{
    base *b = new derived;
    
    delete b;    
    
    return 0;
}
