#include <cstddef>
#include <initializer_list>
#include <iostream>

template<class... Args>
std::size_t fun(Args&&...)
{
    return sizeof...(Args);    
}

int main()
{
    std::cout << fun(1, 2, 3);   // 3
    std::cout << fun(1, (2, 3)); // 2
    
    auto i3 = { 1, 2, 3 };
    auto i2 = { 1, (2, 3) };
    
    std::cout << i3.size(); // 3
    std::cout << i2.size(); // 2
}
