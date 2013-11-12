#include <iostream>
#include <vector>

template<typename C>
auto pop_back_copy(C& _container) -> typename C::value_type
{
    auto copy = std::move(_container.back());
    _container.pop_back();
    return copy;
}

auto main(int, char**) -> int
{
    std::vector<int> v{ 1, 2, 3, 4, 5, 6, 7 };
    auto a = pop_back_copy(v);
    std::cout << a << std::endl;
    
    return 0;
}
