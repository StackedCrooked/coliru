#include <boost/functional/hash.hpp>

#include <fstream>
#include <unordered_set>

#include <iostream>
#include <vector>

int main() {
    using elem_t = std::pair<int, int>;
    std::unordered_set<elem_t, boost::hash<elem_t>> data;
    std::ifstream inFile;
    int a, b;
    while (inFile >> a >> b) {
        data.emplace(std::minmax(a, b));
    }
    
    std::vector<elem_t> vec;
    vec.emplace_back(1, 4);
    vec.emplace_back(5, 6);
    vec.emplace_back(4, 5);
    vec.emplace_back(4, 5); 
    vec.emplace_back(5, 4);
    vec.emplace_back(6, 7);
    std::sort(std::begin(vec), std::end(vec));
    vec.erase(std::unique(std::begin(vec), std::end(vec)));
    
    for (const auto & elem : vec) {
        std::cout << elem.first << "|" << elem.second << ", ";
    }
}
