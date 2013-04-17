#include <iostream>

    struct A
    {
        A() { std::cout << "A" << std::endl; throw 1; }
    };
    
    
void foo()
{
    static A a;
}


int main()
{
    for (int i = 0; i != 10; ++i)
    {
        try
        {
            foo();
        }
        catch (int)
        {
            
        }
    }
}