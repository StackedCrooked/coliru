#include <iostream>
#include <algorithm>
#include <vector>
 
int main()
{
    int n1 = 3;
    int n2 = 5;
 
    std::vector<int> v{0, 1, 2, 3, 4};
 
    auto result1 = std::find(v.begin(), v.end(), n1);
    auto result2 = std::find(v.begin(), v.end(), n2);
 
    if (result1 != v.end()) {
        std::cout << "v содержит: " << n1 << '\n';
    } else {
        std::cout << "v не содержит: " << n1 << '\n';
    }
 
    if (result2 != v.end()) {
        std::cout << "v содержит: " << n2 << '\n';
    } else {
        std::cout << "v не содержит: " << n2 << '\n';
    }
}