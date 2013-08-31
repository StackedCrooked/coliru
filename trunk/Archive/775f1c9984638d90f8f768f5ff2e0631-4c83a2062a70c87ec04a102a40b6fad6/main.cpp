#include <iostream>

void function(int nextFoo)
{
    static int lastFoo=nextFoo; 
    
    std::cout << "lastFoo: " << lastFoo << std::endl ;
    
    if (nextFoo!=lastFoo) 
    {
         std::cout << "here" << std::endl ;
    }
    lastFoo=nextFoo;
}

int main()
{
    function(10) ;
    function(11) ;
    
}