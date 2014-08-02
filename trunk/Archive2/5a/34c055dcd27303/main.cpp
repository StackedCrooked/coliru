#include <iostream>

struct loud
{
    ~loud() { std::cout << "~loud()\n"; }
};

struct T
{
    loud l;
    
    ~T() noexcept(false)
    try
    {
        std::cout << "throwing an int\n";
        throw 42;
    }catch(int)
    {
        std::cout << "caught an int\n";
        throw;
    }
};

int main()
{
    try
    {
        T t;
    }catch(...)
    {
        std::cout << "caught an exception in main\n";
    }
}