#include <iostream>
#include <cstdint>

template<typename T>
void print()
{
    std::cout << __PRETTY_FUNCTION__ << " (size=" << sizeof(T) << ")\n";
}

int main()
{
    print<char>();
    print<signed char>();
    
    
    
    
}