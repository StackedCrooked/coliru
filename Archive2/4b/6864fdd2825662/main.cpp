#include <iostream>

struct A
{
    void* operator new(std::size_t n)
    {
        std::cout << "new\n";
        return ::operator new(n);
    }
    
    void operator delete(void* p)
    {
        std::cout << "delete\n";
        ::operator delete(p);
    }
    
    A()
    {
        std::cout << "A()\n";
        throw 0;
    }
    
    ~A()
    {
        std::cout << "~A()\n";
    }
};

int main()
{
    try
    {
        auto p = new A;
        (void)p;
    }
    catch (...)
    {
        std::cout << "catch\n";
    }
    return 0;
}