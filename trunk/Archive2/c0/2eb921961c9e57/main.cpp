#include <type_traits>
#include <iomanip>
#include <iostream>

int cx = 42;
int const* pcx = &cx;

int main()
{
    auto* const& r = pcx;
    
    std::cout << std::boolalpha;
    
    std::cout << std::is_same<decltype(r), int const* const&>();
}