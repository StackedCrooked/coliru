#include <string>
#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <memory>

int main()
{
    std::cout << "SHIFT TO RIGHT: ";
    
    {
        std::vector<int> v { 1, 2, 3, 4, 5, 6 };
        auto it = v.begin()+3; // number 4
        
        std::rotate(it, it+1, v.end());
        
        std::for_each(v.begin(), v.end(), [](int i) {
            std::cout << i << ", ";
        });
    }
    
    std::cout << std::endl << std::endl << "SHIFT TO LEFT: ";
    
    {
        std::vector<int> v { 1, 2, 3, 4, 5, 6 };
        auto it = v.begin()+3; // number 4
        
        std::reverse_iterator<std::vector<int>::iterator> rit(it+1);
        
        std::rotate(rit, rit+1, v.rend());
        
        std::for_each(v.begin(), v.end(), [](int i) {
            std::cout << i << ", ";
        });
    }
    
    std::cout << std::endl;
}