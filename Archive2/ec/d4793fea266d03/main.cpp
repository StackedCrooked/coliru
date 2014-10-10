#include <array>
#include <iostream>
#include <string>
#include <map>
#include <random>
 
int main() {
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> rng5(1, 5);

    int index = 0;
    std::array<std::array<int, 5>, 7> bad = {{
        {{1, 2, 3, 4, 5}}
        , {{2, 3, 4, 5, 6}}
        , {{3, 4, 5, 6, 7}}
        , {{4, 5, 6, 7, 1}}
        , {{5, 6, 7, 1, 2}}
        , {{6, 7, 1, 2, 3}}
        , {{7, 1, 2, 3, 4}}
    }};
    std::map<int, int> hist;
    for (int n = 0; n < 100000; ++n) {
        index = (index + 1) % 7;
        auto sum = bad[index][rng5(gen)-1];
        ++hist[sum];
    }
    for (auto p : hist) {
        std::cout << p.first << ' ' << std::string(p.second/100, '*') << '\n';
    }
}
