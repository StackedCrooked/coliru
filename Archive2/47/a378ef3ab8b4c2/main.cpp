#include <cstddef>
#include <utility>
#include <iostream>

void print(std::initializer_list<int> il)
{
    for (auto&& elem : il) std::cout << elem << std::endl;
}

int main()
{
    auto indexed_lambda = [] <std::size_t... Is> (std::index_sequence<Is...>) { print({Is...}); };
    
    indexed_lambda(std::make_index_sequence<5>{});    
}
