#include <cassert>
#include <cstring>
#include <iostream>

struct Item1
{
    virtual void v0(){}
};

struct Item2
{
    virtual void v0(){}
    virtual void v1(){}
};

struct Item3
{
    virtual void v0(){}
    virtual void v1(){}
    virtual void v2(){}
};

struct Item4
{
    virtual void v0(){}
    virtual void v1(){}
    virtual void v2(){}
    virtual void v4(){}
};


struct Item12 : Item1, Item2 {};
struct Item123 : Item1, Item2, Item3 {};
struct Item1234 : Item1, Item2, Item3, Item4 {};


int main()
{
    std::cout << "Does the number of virtual methods affect the object size?" << std::endl;    
    std::cout << "sizeof Item1: " << sizeof(Item1{}) << std::endl;
    std::cout << "sizeof Item2: " << sizeof(Item2{}) << std::endl;
    std::cout << "sizeof Item3: " << sizeof(Item3{}) << std::endl;    
    std::cout << " => So Vtable is not laid out in the object. It's probably a pointer to array." << std::endl;
    
    
    std::cout << "\nDoes the number of base classes affect the object size?" << std::endl;            
    std::cout << "sizeof Item12{}: " << sizeof(Item12{}) << std::endl;    
    std::cout << "sizeof Item123{}: " << sizeof(Item123{}) << std::endl;    
    std::cout << "sizeof Item1234{}: " << sizeof(Item1234{}) << std::endl;    
    std::cout << "=> It seems the VTable pointer of each inherited class is a \"field\" in the most derived object." << std::endl;
        
    Item4 item4;
    
    struct Item4_Analyzed
    {
        // Define the function pointer type.
        typedef void(*Function)();
        
        // VTable is an array of Function pointer objects.
        typedef Function* VTable;
        
        // First entry in object is vtable.
        VTable* vtable;
    };
    
    
    Item4_Analyzed item4_analyzed;
    assert(sizeof(item4) == sizeof(item4_analyzed));
    
    // copy our data
    memcpy(&item4_analyzed, &item4, sizeof(item4));
    
    
    
    std::cout << "\nLet's see if we can iterate over the Vtable entries:" << std::endl;
    
    // print until segfault
    std::cout << "Index\tVTABLE\t\tEntry\t\t*Entry" << std::endl;
    for (int i = 0; i != 100; ++i)
    {
        if (i == 4) // Item4 has 4 virtual methods, so probably out-of-bounds access starts here.
        {
            std::cout << "Welcome to UB land!" << std::endl;
        }
        auto vtable = item4_analyzed.vtable;
        auto function = vtable[i];
        std::cout << i << "\t" << vtable << "\t" << function << "\t" << std::flush;
        std::cout << (*function) << std::endl;
    }    
}