#include <iostream>
#include <vector>
#include <string>

int main() {
    std::vector<int> intVector;

    int x = 100;
    
    
    for (const auto digit : std::to_string(x)) {
        intVector.push_back(digit - '0');
    }    
    
    for (const auto e : intVector) {
        std::cout << e << std::endl;    
    }
}