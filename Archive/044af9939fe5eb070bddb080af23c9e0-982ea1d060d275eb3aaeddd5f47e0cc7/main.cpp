#include <cassert>
#include <cstring>
#include <iostream>

struct Item1
{
    virtual ~Item1(){}
    virtual void a(){}
    
    unsigned long l = 123456789;
};

struct Item2
{
    virtual ~Item2(){}
    virtual void b(){}
    virtual void c(){}
};

struct Item3
{
    virtual ~Item3(){}
    virtual void d(){}
    virtual void e(){}
    virtual void f(){}
};

struct Item4
{
    virtual ~Item4(){}
    virtual void g(){}
    virtual void h(){}
    virtual void j(){}
    virtual void i(){}
};

struct Item12 : Item1, Item2 {};
struct Item123 : Item1, Item2, Item3 {};
struct Item1234 : Item1, Item2, Item3, Item4 {};

int main()
{
    // number of virtual methods does not affect object size
    std::cout << sizeof(Item1{}) << std::endl;
    std::cout << sizeof(Item2{}) << std::endl;
    std::cout << sizeof(Item3{}) << std::endl;
    
    // number of base classes *does* affect object size
    std::cout << sizeof(Item12{}) << std::endl;
    std::cout << sizeof(Item123{}) << std::endl;
    std::cout << sizeof(Item1234{}) << std::endl;
    
    
    Item1 item1;
    
    
    struct Item1_Analyzed
    {
        unsigned int** vtable;
        unsigned long b;
    };
    
    
    Item1_Analyzed item1_analyzed;
    assert(sizeof(item1) == sizeof(item1_analyzed));
    
    
    memcpy(&item1_analyzed, &item1, sizeof(item1));
    for (int i = 0; i != 100; ++i)
    {
        auto vtable = (*item1_analyzed.vtable);
        auto entry_ptr = vtable + i;
        std::cout << i << "\t" << entry_ptr << std::flush << "\t" << (*entry_ptr) << std::endl;
    }
    
    std::cout << item1_analyzed.b << std::endl;
    
}