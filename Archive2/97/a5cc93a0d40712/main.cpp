#include <initializer_list>
#include <type_traits>

int main() {
    auto x = { 1, 2, 3 };
    static_assert(std::is_same<decltype(x), std::initializer_list<int>>::value, "...");
}