#include <unordered_map>
#include <tuple>
#include <utility>
#include <iostream>

int main()
{
    std::unordered_map<int, std::pair<std::string, std::string>> my_map;
    
    my_map.emplace(std::piecewise_construct,
      std::forward_as_tuple(1),
      std::forward_as_tuple("foo", "bar"));
      
    std::cout << my_map[1].first << std::endl;
}
