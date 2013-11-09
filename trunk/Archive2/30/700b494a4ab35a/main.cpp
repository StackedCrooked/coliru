#include <iostream>

class Thing
{
    
};

int Thing()
{
    return 42;   
}

void function(class Thing thing)
{
    std::cout << "Class";
}

void function(int number)
{
    std::cout << "Number";   
}


int main()
{
    function(typename ::Thing());
}