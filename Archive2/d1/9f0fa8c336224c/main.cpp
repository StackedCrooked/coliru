#include <iostream>

struct Exceptions
{};

struct NoExceptions
{};

struct A_base
{
    int doStuff()
    {std::cout << "Im doin smth." << std::endl; return 0;}
};

template<typename T>
struct A : A_base
{ };

template<>
struct A<NoExceptions> : A_base
{
    int a() noexcept
    {return doStuff();}
};

template<>
struct A<Exceptions> : A_base
{
    void a() throw(int)
    {if(!doStuff()) throw 1;}
};

int main()
{
    A<NoExceptions> myA0;
    A<Exceptions> myA1;
    
    std::cout << myA0.a() << std::endl;
    
    try{myA1.a();}
    catch(int a)
    {std::cout << a;}
}