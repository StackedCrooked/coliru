#include <iostream>
#include <vector>

struct stuff {
    std::vector<int> list;
    stuff() : list({0, 1, 2, 3, 4}) {}
};

int main() {
    stuff test;
    std::cout << test.list[1];
}