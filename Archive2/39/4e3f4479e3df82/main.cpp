#include <iostream>
#include <algorithm>
#include <map>

using MMap = std::multimap<int, int>;

int main()
{
    MMap map;
    int values[] = {4, 5, 6, 5, 4, 6};
    int ID[] = {0, 1, 2, 3, 4, 5};
    for (int k = 0; k < 6; k++)
        map.emplace(values[k], k);
    
    int k = 0;
    for (auto mapped : map) {
        std::cout << mapped.first << " " << mapped.second << std::endl;
        ID[mapped.second] = k++ - mapped.second; 
    }
    
    std::cout << "\nThe expected movement of each value in the array\n"
              << "(-v means move left v times otherwise move right)\n\n";
    for (auto p : ID) {
        std::cout << p << " ";
    }
    return 0;
}