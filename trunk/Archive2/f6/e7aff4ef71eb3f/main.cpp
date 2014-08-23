#include <type_traits>
#include <iomanip>
#include <iostream>

int main()
{
    int x = 42;
    int const cx = x;
    int const& rcx = cx;
     
    auto a = x;
    auto b = cx;
    auto c = rcx;
    
    std::cout << std::boolalpha;
    
    std::cout << std::is_same<decltype(a), int>() << std::endl;
    std::cout << std::is_same<decltype(b), int>() << std::endl;
    std::cout << std::is_same<decltype(c), int>() << std::endl;
}