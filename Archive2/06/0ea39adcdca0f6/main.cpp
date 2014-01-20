#include <iostream>
#include <memory>
#include <vector>

struct test {
    ~test() {
        std::cout << "Destructed\n";
    }
};

int main() {
    std::vector<std::shared_ptr<test>> vector;
    {
        vector.emplace_back(new test());
        vector.emplace_back(new test());
        std::cout << "---- point a\n";
    }
    std::cout << "---- point b\n";
}