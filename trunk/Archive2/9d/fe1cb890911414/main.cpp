#include <iostream>

class Thing
{
    
};

int Thing()
{
    return 42;   
}

void function(Thing thing)
{
    std::cout << "Class";
}

void function(int number)
{
    std::cout << "Number";   
}


int main()
{
    function(Thing());
}