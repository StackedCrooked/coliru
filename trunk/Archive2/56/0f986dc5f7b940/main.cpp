#include <type_traits>
#include <iomanip>
#include <iostream>

int cx = 42;
int const* pcx = &cx;

template<typename T>
void foo(T* const& r)
{
    std::cout << std::is_same<decltype(r), int const* const&>() << std::endl;
}

int main()
{
    std::cout << std::boolalpha;    

    auto* const& r = pcx;    
    std::cout << std::is_same<decltype(r), int const* const&>() << std::endl;
    
    foo(pcx);
}