int x = 10;

auto f() -> decltype((x)) {
    return (x);
}

#include <type_traits>

int main() {
    static_assert(std::is_lvalue_reference<decltype(f())>::value, "...");
}