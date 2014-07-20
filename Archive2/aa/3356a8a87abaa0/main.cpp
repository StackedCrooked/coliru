#include <algorithm>
#include <string>
#include <iostream>
#include <vector>

int main() {
    std::vector<std::pair<std::string, int>> arr;
    arr.emplace_back("AP", 7);
    arr.emplace_back("GP", 93);
    
    std::cout << std::get<0>(arr[0]) << '\n';
    std::cout << std::get<0>(arr[1]) << '\n';
    
    std::cout << std::get<1>(arr[0]) << '\n';
    std::cout << std::get<1>(arr[1]) << '\n';
}