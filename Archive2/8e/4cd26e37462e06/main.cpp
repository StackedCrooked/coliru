#include <vector>
#include <iostream>
#include <algorithm>
 
int main()
{
    std::vector<int> v({1,2,3});
    for (const auto& value : v) {
        std::cout << value << " ";
    }
    std::cout << '\n';
 
    std::vector<int> destiny(3);
    std::reverse_copy(std::begin(v), std::end(v), std::begin(destiny));
    for (const auto& value : destiny) {
        std::cout << value << " ";
    }
    std::cout << '\n';
}