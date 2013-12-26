#include <algorithm>
#include <iostream>
#include <vector>

template <typename T>
std::ostream & operator<<(std::ostream & out, std::vector<T> vec) {
    for (const auto & elem : vec) {
        out << elem << " ";
    }
    return out;
}

int main() {
    std::mt19937 rng(std::random_device{}());
    std::vector<int> vec(20);
    std::iota(begin(vec), end(vec), 0);
    std::cout << vec << '\n';
    std::shuffle(begin(vec), end(vec), rng);
    std::cout << vec << '\n';
}