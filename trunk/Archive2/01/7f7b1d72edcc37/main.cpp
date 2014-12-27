#include <iostream>

namespace A 
{
    namespace B
    {
        enum E : int;
    }
}
namespace C
{
    using A::B::E;
}

enum C::E : int { x = 2 };

int main()
{ 
}