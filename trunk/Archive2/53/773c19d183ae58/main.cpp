#include <type_traits>

template <bool B>
struct foo {};

int main() {
    foo<(std::is_const<int>())> x;
}