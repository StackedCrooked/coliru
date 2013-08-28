#include <algorithm>
#include <iostream>
#include <string>

int main() {
    std::string str{"12345"};
    
    auto product = std::accumulate(std::begin(str), std::end(str), 1, [](int total, char c) {
        return total * (c - '0');
    });   
    
    std::cout << product;
}