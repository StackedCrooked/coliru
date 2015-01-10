#include <algorithm>
#include <iostream>
#include <string>
#include <vector>


int main() {
    // As integer
	std::vector<int> input = {
        4, 3, 9, 1, 0 , 10, 101, 01
    };
    std::sort(std::begin(input), std::end(input));
    
    for (const auto& e : input) {
        std::cout << e << ", ";    
    }
    std::cout << std::endl;
    
    // As string
    std::string str = "4210";
    
    std::sort(std::begin(str), std::end(str));
    
    for (const auto& e : str) {
        std::cout << e << ", ";    
    }
}