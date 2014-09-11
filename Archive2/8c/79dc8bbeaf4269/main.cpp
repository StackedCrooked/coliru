#include <unordered_map>
#include <tuple>
#include <utility>
#include <iostream>

int main()
{
    std::unordered_map<int, std::pair<std::string, std::string>> my_map;
    
    std::string a = "foo";
    std::string b = "bar";
    
    my_map.emplace(std::piecewise_construct,
      std::forward_as_tuple(1),
      std::forward_as_tuple(std::move(a), std::move(b)));
      
    std::cout << my_map[1].first << std::endl;
    std::cout << my_map[1].second << std::endl;
}
