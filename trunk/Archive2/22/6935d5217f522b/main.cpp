#include <iostream>
#include <map>

using Map = std::multimap<int, int>;


int main()
{
    Map map;
    int values[] = {4, 5, 6, 5, 4, 6};
    for (int k = 0; k < 6; k++)
        map.emplace(values[k], k);
    
    for (auto mapped : map)
        std::cout << mapped.first << " " << mapped.second << std::endl;
}