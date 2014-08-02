#include <iostream>

struct loud
{
    loud() { std::cout << "loud()\n"; }
    ~loud() { std::cout << "~loud()\n"; }
};

struct A
{
    A() { std::cout << "A()\n"; }
    ~A() noexcept(false) { std::cout << "~A()\n"; throw 42; }
};

struct T
{
    loud l;
    A a;
    
    ~T() noexcept(false)
    try
    {
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