#include <iostream>

class x
{
};

namespace
{
    class x
    {
    };
    
    int x;
    
    ::x x;
}

int main()
{
    return 0;
}
