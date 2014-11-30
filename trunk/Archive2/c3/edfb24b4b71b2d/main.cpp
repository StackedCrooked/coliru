#include <algorithm>
#include <tuple>
#include <iostream>
#include <map>

int main() {
    std::map<std::string, int> map;
    map["a"] = 123;
    map["b"] = 321;
    for (auto p : map)
        std::cout << std::get<0>(p) << ':' << std::get<1>(p) << '\n';
}