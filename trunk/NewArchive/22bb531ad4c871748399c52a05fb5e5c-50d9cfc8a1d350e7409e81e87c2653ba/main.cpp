#include <cstdio>


void* operator new(std::size_t)
{    
    puts("Hello");
}


void operator delete(void *)
{    
    puts("World!");
}


int main()
{   
    delete new int;
}