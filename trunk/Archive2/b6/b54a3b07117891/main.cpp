#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <map>

    
std::unordered_map<int, std::unique_ptr<int>> container;

int main()
{
    std::unique_ptr<int> ptr_one{new int(1)};
    
    container.emplace(std::make_pair(1, std::move(ptr_one)));
    container.emplace(std::make_pair(1, std::unique_ptr<int>(new int(2))));
}
