#include <stdexcept>

constexpr int f(int x) {
    return (x < 0) ? throw std::runtime_error("error") : x;
}

int main(int argc, char **argv) {
    f(-5);
    return 0;
}