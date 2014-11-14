#include <map>
#include <iostream>

int main() {
    std::map<int, int> x = {
        { 10, 11 },
        { 11, 12 },
        { 12, 13 }
    };
    
    for(auto& p : x) {
        p.second = 15;
    }
    
    for(auto&& p : x) {
        std::cout << "(" << p.first << ", " << p.second << ")\n";
    }
}