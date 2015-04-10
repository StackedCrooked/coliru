#include <iostream>
#include <vector>

int main() {
    size_t a = 3;
    size_t b = 1;
    std::vector<size_t> v1{a,b};
    std::vector<size_t> v2(a,b);
    std::cout << "v1\n";
    for (auto x:v1)
        std::cout << x << '\n';
    std::cout << "v2\n";
    for (auto x:v2)
        std::cout << x << '\n';
}