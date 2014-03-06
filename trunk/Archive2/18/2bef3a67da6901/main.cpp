#include <iostream>

class A 
{
    public: 
        int x; 
        
        A() : x(666) {}
};


int main()
{
    A A; 
    std::cout << A.x << std::endl;
}
