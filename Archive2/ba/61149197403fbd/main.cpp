#include <iostream>

int main()
{
    auto a = []{ return 0; };
    
    return noexcept(a());
}