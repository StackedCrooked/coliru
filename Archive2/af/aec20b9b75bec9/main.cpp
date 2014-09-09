#include <memory>
#include <iostream>
#include <utility>

struct basic {
    std::unique_ptr<int> x;
};

int main() {
    std::cout << std::boolalpha << noexcept(basic(std::declval<basic>())) << '\n';
}