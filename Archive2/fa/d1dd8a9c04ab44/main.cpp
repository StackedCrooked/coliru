#include <algorithm>
#include <vector>
#include <iterator>
#include <utility>
#include <unordered_map>
#include <iostream>
    
    std::vector<std::pair<int, int>> find(const std::unordered_multimap<int, int> & thing, int key, int value) {
        std::vector<std::pair<int, int>> ret;
        auto range = thing.equal_range(key);
        std::copy_if(range.first, range.second, std::back_inserter(ret),
                     [value](const std::pair<const int, int> &p) 
                     { return p.second != value; });
        return ret;
    }
    
    int main() {
            std::unordered_multimap<int, int> set =  {{1,2},{1,5},{1,6},{2,4},{3,5},{4,6},{6,7},{6,8}};
        for(const auto &p : find(set,1,5)) {
            std::cout <<p.first << ' ' << p.second << '|';
        }
        std::cout << '\n';
        for(const auto &p : find(set,2,4)) {
            std::cout <<p.first << ' ' << p.second << '|';
        }
        std::cout << '\n';
        for(const auto &p : find(set,10,20)) {
            std::cout <<p.first << ' ' << p.second << '|';
        }
        std::cout << '\n';
        for(const auto &p : find(set,6,7)) {
            std::cout <<p.first << ' ' << p.second << '|';
        }
        std::cout << '\n';
    }