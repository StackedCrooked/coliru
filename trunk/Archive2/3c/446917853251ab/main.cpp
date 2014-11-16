#include <map>

using map_type = std::map<std::pair<int, int>, int>;

map_type to_map(std::initializer_list<int> l) {
    if(l.size() % 3 != 0) {
        return {};
    }

    map_type result;
    for(auto begin = l.begin(); begin != l.end(); begin += 3) {
        result.emplace(std::make_pair(*begin, *(begin + 1)), *(begin + 2));
    }
    return result;
}

#include <iostream>

int main() {
    auto p = {1,1,0,1,2,1,1,3,1};
    auto m = to_map(p);
    for(auto&& i : m) {
        std::cout << '(' << i.first.first << ", " << i.first.second << ") --> " << i.second << '\n';
    }
}