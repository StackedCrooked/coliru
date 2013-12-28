#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
 
int main()
{
    std::vector<int> v {3, 1, 4, 1, 5, 9, 2, 6}; 
    std::srand(std::time(0));
    std::pair<int, int> bounds = std::minmax(v);
 
    std::cout << "v[" << bounds.first << "," << bounds.second << "]: ";
    for (int i = bounds.first; i < bounds.second; ++i) {
        std::cout << v[i] << ' ';
    }
    std::cout << '\n';
}