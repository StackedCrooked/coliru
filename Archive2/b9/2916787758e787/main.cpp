#include <stdexcept>

constexpr int f(int x) {
    return (x < 0) ? throw std::runtime_error("error") : x;
}

template<int X> struct foo { };

int main(int argc, char **argv) {
    foo<f(-5)>{};
    return 0;
}