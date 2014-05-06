// g++ -std=c++11 -fPIC -c main.cpp

#include <stdexcept>
#include <iostream>
#include <dlfcn.h>


void *malloc(size_t size)
{
    std::cout << "malloc(" << size << ")" << std::endl;   
    
    typedef void* (*AllocFunction)(size_t);
    static AllocFunction real_malloc = reinterpret_cast<decltype(real_malloc)>(dlsym(RTLD_NEXT, "malloc"));
    return real_malloc(size);
}