#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

#define IMPLEMENT_MEM_OPS(cname) \
    public: \
        static void* operator new(size_t bytes) { return malloc(bytes); } \
        static void operator delete(void* mem)  { cname* self = reinterpret_cast<cname*>( mem ); self->~cname(); free(mem); }

struct Foo
{
    Foo()
    {
        std::cout << "Created Foo!" << std::endl;
    }
    virtual ~Foo()
    {
        std::cout << "Destroyed Foo!" << std::endl;
    }
    IMPLEMENT_MEM_OPS( Foo );
};

struct Bar
{
    Bar()
    {
        std::cout << "Created Bar!" << std::endl;
    }
    ~Bar()
    {
        std::cout << "Destroyed Bar!" << std::endl;
    }
    IMPLEMENT_MEM_OPS( Bar );
};

int main()
{
    int* i = new int();
    *i = 42;
    
    Foo* f = new Foo();
    Bar* b = new Bar();
    
    delete b;
    delete f;
    delete i;
    return 0;
}
