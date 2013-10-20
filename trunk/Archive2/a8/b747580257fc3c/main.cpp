#include <iostream>
#include <vector>

int main() {
    std::vector<bool> vec1{true, false};
    
    std::cout << std::boolalpha;
    
    for (auto i : vec1)
        std::cout << i << " ";
    std::cout << std::endl;

    for (auto i : vec1)//i is a bit reference
        i = false;
    
    for (auto i : vec1)
        std::cout << i << " ";
    std::cout << std::endl;
        
    
    std::vector<int> vec2{1,0};
    
    for (auto i : vec2)
        std::cout << i << " ";
    std::cout << std::endl;

    for (auto& i : vec2)
        i = 0;
    
    for (auto i : vec2)
        std::cout << i << " ";
    std::cout << std::endl;
}