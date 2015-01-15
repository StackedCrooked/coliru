#include <list>
#include <iostream>
#include <iterator>
 
struct Mother
{
    Mother()
    {
        std::cout << "calling construction from mother construction\n";
        construction();
    
    }
    ~Mother()
    {
        std::cout << "calling destruction from mother destruction\n";
        destruction();
    }
virtual void destruction()
{
    std::cout << "Mother destruction\n";
}
virtual void construction()
{
    std::cout << "Mother construction\n";
}
};

struct Child : public Mother
{
virtual void destruction() override
{
    std::cout << "Child destruction\n";
}
virtual void construction() override
{
    std::cout << "Child construction\n";
}
    
};


int main( )
{
   Child child;
   return 0;
}