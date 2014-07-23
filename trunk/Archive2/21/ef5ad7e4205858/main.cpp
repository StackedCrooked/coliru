#include <iostream>

int main()
{
    auto a = [] () noexcept {};
    
    return noexcept(a());
}