#include <cmath>
#include <iostream>
#include <vector>

struct A {
    bool b{false};
};


int main() {
    std::vector<int> a(4);
    a.push_back(5);
    for (auto & ai : a) {
        std::cout << ai << std::endl;
    }
}