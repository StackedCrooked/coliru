#include <array>

void f() {
    std::array<int, 42> array;
    array.fill(1);
    array.fill(2);
}

int main() {
    f();
    return 0;
}