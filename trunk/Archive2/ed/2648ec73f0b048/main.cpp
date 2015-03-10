#include <iostream>

class A
{
    public:
    A()
    {
    std::cout << "in cte" <<std::endl;    
    }
    
    A(const A &copy)
    {
    std::cout <<"in copy cte" << std::endl;
    }
    
    A& operator=(const A& copy)
     {
     std::cout << "in assignment operator" << std::endl;      
     }
};

int main()
{
 auto myvar = A{};
 auto myvar2 =myvar;
 myvar = myvar2;
}