#include <iostream>
#include <map>


void print(const std::multimap<std::string, std::string>& map) {
    for(const auto& e : map) {
        std::cout << e.first << ", " << e.second << std::endl;
    }
    
    std::cout << std::endl;
}


int main() {
    std::multimap<std::string, std::string> map = {
       {"A", "a1"}, {"A", "a2"}, {"B", "b"}
    };
    
    // Goal: Replace the two elements with the key "A" with another, single, value
    
    // Method 1 - Erase all and emplace
    // Advantages: simple and intuitive
    // Disadvantages: two lookups for erase and emplace
    auto map1 = map;
    map1.erase("A");
    map1.emplace("A", "a");
    print(map1);
    
    // Method 2 - Replace one of the existing elements and erase the rest;
    //              emplace if key doesn't exist
    // Advantages: only one lookup (equal_range) and no additional allocation
    //              when elements already exist
    // Disadvantage: much more complex
    auto map2 = map;
    auto range = map2.equal_range("A");
    if(range.first != map2.end()) {
        range.first->second = "a";
        map2.erase(++range.first, range.second);
    }
    else {
        map2.emplace("A", "a");
    }
    print(map2);
}