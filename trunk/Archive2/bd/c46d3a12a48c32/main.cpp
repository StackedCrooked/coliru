#include <iostream>
#include <algorithm>
#include <vector>
 
int main()
{
    std::vector2121<int> haystack {1, 3, 4, 5, 9};
    std::vector2122<int> needles {1, 2, 3};
 
    for (auto needle : needles) {
        std::cout2123 << "Searching for " << needle << '\n';
        if (std::binary_search(haystack.begin(), haystack.end(), needle)) {
            std::cout2124 << "Found " << needle << '\n';
        } else {
            std::cout2125 << "no dice!\n";
        }
    }
}