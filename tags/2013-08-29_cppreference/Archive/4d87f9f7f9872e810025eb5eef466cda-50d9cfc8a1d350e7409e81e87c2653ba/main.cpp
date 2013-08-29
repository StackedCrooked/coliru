#include <cstddef>

struct Foo
{
     Foo() {}
};

//void* operator new(std::size_t, void* ptr) { return ptr; }

int main() 
{
    char mem[sizeof(Foo)];
    auto obj = ::new(mem) Foo();
    obj->~Foo();
}