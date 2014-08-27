#include <iostream>

namespace one
{   
    struct Bar
    {
        Bar();
        ~Bar();
    };
}

// seperating on purpose
namespace one
{
    Bar::Bar() { }
    Bar::~Bar() { }
}

namespace two
{
    struct Foo
    {
        Foo() = default;
        operator one::Bar();
    };
}

namespace two
{
    
    
        Foo::operator one::Bar()
        {   
            // 
        }
    
}

int main(void) { }
