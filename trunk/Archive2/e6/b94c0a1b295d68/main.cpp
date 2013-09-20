#include <iostream>
#include <vector>

struct A {
 virtual ~A() = default;
 virtual std::vector<int> operator()() const = 0;
};

struct B : public A {
    auto operator()() const -> std::vector<int> override {
        return std::vector<int>{};
    }
};

int main() {
    std::cout << __VERSION__ << std::endl;
    A *b = new B;
    b->operator()();
}