#include <vector>
#include <utility>
#include <string>
#include <iostream>

int main()
{
    std::vector<std::pair<std::string, int>> v = 
    {
        {"something", 42}
    };
    
    std::cout << v.at(0).first << ' ' << v.at(0).second << std::endl;
}