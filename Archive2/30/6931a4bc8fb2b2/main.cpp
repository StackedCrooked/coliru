#include <iostream>
#include <vector>
#include <tuple>

template <typename... T>
auto getPushBackFunctionPointers() -> std::tuple<void(std::vector<T>::*)(T const&)...>
{
    return std::make_tuple(&std::vector<T>::push_back...);
}

int main()
{
    
}