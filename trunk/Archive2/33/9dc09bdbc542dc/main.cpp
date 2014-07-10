#include <iostream>

bool SomeExpensiveComputation()
{
    std::cout << "D'oh!" << std::endl;
    return true;
}

int main()
{
    int value = 42;
    
    if ( value > 0 || SomeExpensiveComputation() )
    {
        std::cout << "Example 1" << std::endl;
    }
    
    bool b1 = value > 0;
    bool b2 = SomeExpensiveComputation();
    
    if ( b1 || b2 )
    {
        std::cout << "Example 2" << std::endl;
    }
}