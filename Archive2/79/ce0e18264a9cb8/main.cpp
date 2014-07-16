#include <type_traits>

int main() {
    int foo();
    static_assert(std::is_same<decltype(foo), int()>::value, "Not a function");
    static_assert(std::is_same<decltype(foo), int(*)()>::value, "Not a function pointer");
}