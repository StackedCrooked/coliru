#include <stdexcept>

constexpr int f(int x) {
    return x > 0 ? x * 10 : throw std::runtime_error("...");
}

int main() {
    constexpr auto x = f(0);
}