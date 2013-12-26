#include <iostream>
#include <map>
#include <random>
 
int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::discrete_distribution<> d({40, 10, 10, 40});
    // 1 is 40%
    // 2 is 10%
    // 3 is 10%
    // 4 is 40%
    std::map<int, int> m;
    for(unsigned i = 0; i < 10000; ++i) {
        ++m[d(gen)];
    }
    for(auto&& p : m) {
        std::cout << p.first << " generated " << p.second << " times\n";
    }
}