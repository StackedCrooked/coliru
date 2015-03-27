#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>



int main()
{
    std::unordered_map<int, std::unordered_map<int, double>> myUMap;
    myUMap[5].insert(std::make_pair(1, 1.0));
    
    for(auto&& e: myUMap[5]) {
        std::cout << e.first << " " << e.second << std::endl;
    }
}
