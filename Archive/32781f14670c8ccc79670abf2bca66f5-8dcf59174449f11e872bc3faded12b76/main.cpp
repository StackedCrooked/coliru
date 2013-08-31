#include <array>
#include <initializer_list>

int main() {
    std::initializer_list<int> l = { 1, 2, 3 };
    std::array<int, 3> a(l);
}