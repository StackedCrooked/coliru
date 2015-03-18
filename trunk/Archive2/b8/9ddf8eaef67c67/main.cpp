#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::vector<std::pair<int, std::string>> vec;
    
    vec.emplace_back(1, "hello"); // ok
    
    vec.push_back(1, "hello"); // erro
    
    std::cout << vec[0].second << std::endl << vec[1].second;
    
    return 0;
}