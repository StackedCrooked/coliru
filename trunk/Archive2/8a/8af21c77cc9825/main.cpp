#include <type_traits>

constexpr bool b = std::is_const<int>();

int main() {
    foo<b> x;
}