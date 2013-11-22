#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

int main(int, char*[]) {
    std::vector<std::string> cols = {"A", "B", "C"};
    std::vector<std::string> rows = {"1", "2", "3", "4"};
    std::vector<std::string> vec;
    for (auto i : cols)
        for (auto j : rows)
            vec.emplace_back(i + j);
    std::random_shuffle(vec.begin(), vec.end());
    
    for (auto i : vec) std::cout << i << ' ';
    return 0;
}