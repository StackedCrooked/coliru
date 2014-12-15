#include <iostream>
#include <functional>

using namespace std::placeholders;

class Foo
{
public:
    Foo(const char* myString) {
        std::cout << "Foo::Foo, myString=" << myString << std::endl;
    }
};

void create_Foo(void *memory, const char *myString)
{
    new (memory) Foo(myString);
}    

int main()
{
    void (*create)(void *) = nullptr;    
    
    const char *str = "asdf";
    
    create = [str](void *mem) { create_Foo(mem, str); };
    
    char data[1024];
    create(data);    
}
