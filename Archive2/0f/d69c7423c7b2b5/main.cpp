#include <cassert>
#include <cstdlib>
#include <iostream>
#include <unordered_set>

std::unordered_multiset<unsigned long long> factor(unsigned long long x) {
    assert(x >= 0);
    std::unordered_multiset<unsigned long long> result;
    for (auto i = 2ull; x != 1; ++i) {
        while (x % i == 0) {
            result.insert(i);
            x /= i;
        }
    }
    return result;
}

int main(int argc, char const** argv) {
    if (argc != 2) {
        return 1;
    }
    auto x = std::atoll(argv[1]);
    auto result = factor(x);
    std::cout << "factors of " << x << " = {";
    bool had_first = false;
    for (auto f : result) {
        if (had_first) {
            std::cout << ", ";
        }
        had_first = true;
        std::cout << f;
    }
    std::cout << "}\n";
    return 0;
}