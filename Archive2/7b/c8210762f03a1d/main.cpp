#include <array>
#include <atomic>
#include <cassert>
#include <iostream>
#include <typeinfo>
#include <vector>


struct Task
{
    using FunctionPointer = void (*) (void*);    
    
    Task(FunctionPointer fptr, void* storage) : fptr_(fptr), (storage)   // typo, should be `storage_(storage)`
    {
    }
    
    void operator()() { fptr_(storage_); }
    
    FunctionPointer fptr_;
    void* storage_;
};