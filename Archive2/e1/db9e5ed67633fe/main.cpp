#include <string>
#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <memory>

int main()
{
    std::vector<int> v { 1, 2, 3, 4, 5, 6 };
    auto it = v.begin()+3; // number 4
    
    std::rotate(it, it+1, v.end());
    
    std::for_each(v.begin(), v.end(), [](auto i) {
        std::cout << i << std::endl;
    });
}