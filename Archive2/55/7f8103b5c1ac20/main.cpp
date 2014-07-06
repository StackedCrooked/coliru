#include <string>
#include <iostream>
#include <vector>

void print(std::string&& x) {}

int main() {
    std::vector<std::vector<int>> world;
    world.emplace_back(std::vector<int>{
        1, 2, 3
    });
    for (const auto& v : world)
        for (auto i : v)
            std::cout << i << '\n';
}