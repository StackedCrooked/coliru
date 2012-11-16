#ifndef COLIRU_SANDBOX_MEMORY_LIMIT
#error Build command should specify -DCOLIRU_SANDBOX_MEMORY_LIMIT=...
#endif


#include <stdexcept>
#include <iostream>
#include <dlfcn.h>


void *malloc(size_t size)
{
    typedef void* (*AllocFunction)(size_t);
    static AllocFunction real_malloc = reinterpret_cast<decltype(real_malloc)>(dlsym(RTLD_NEXT, "malloc"));

    static std::size_t gSum = 0;
    gSum += size;
    if (gSum > COLIRU_SANDBOX_MEMORY_LIMIT)
    {
        return 0;
    }
    else
    {
        return real_malloc(size);
    }
}
