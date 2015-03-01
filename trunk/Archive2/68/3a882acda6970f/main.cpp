#include <iostream>

struct Exceptions
{};

struct NoExceptions
{};

struct A
{
    int a(NoExceptions n) noexcept
    {return -1;}
    
    int a(Exceptions d) throw(int)
    {throw 1;}
};

int main()
{
    A myA;
    
    std::cout << myA.a(NoExceptions()) << std::endl;
    
    try{myA.a(Exceptions());}
    catch(int a)
    {std::cout << a;}
}