#include <array>

int x = 0;

int main() {
    std::array<int, 0 == 0? 42 : x++> a;
}