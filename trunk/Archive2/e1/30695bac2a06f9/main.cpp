#include <stdexcept>

auto up = std::runtime_error("BELCH");

int main() {
    throw up;
}