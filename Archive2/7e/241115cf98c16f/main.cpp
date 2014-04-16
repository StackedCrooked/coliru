#include <iostream>
#include <algorithm>
#include <map>

using MMap = std::multimap<int, int>;

void insertion(int array[], int len, int *ID = nullptr) {
    static bool STABLE_CHECK = ID != nullptr;
    
    for (int v = 1; v < len; ++v) {
        if (array[v] < array[v - 1]) {
            for(int w = v; w - 1 >= 0 && array[w] < array[w - 1]; w--) {
                std::swap(array[w], array[w - 1]);
                if (STABLE_CHECK) {
                    ID[w]--;
                    ID[w - 1]++;
                }
            }
        }
    }
}

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
    
    insertion(values, 6, ID);
    
    std::cout << "\nThe ID array. A value other than zero means the sort\n"
              << "is not stable\n\n";
    for (auto p : ID) {
        std::cout << p << " ";
    }
    
    return 0;
}