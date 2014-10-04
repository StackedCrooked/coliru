#include <cstring>
#include <type_traits>

struct foo {
    foo() = default;
    foo(const foo&) = delete;
    foo& operator = (const foo&) & = delete;
};

int main() {
    static_assert(!std::is_copy_constructible<foo>{}, "");
    static_assert(!std::is_copy_assignable<foo>{}, "");
    foo a, b;
    static_assert(std::is_trivially_copyable<foo>{}, "");
    std::memcpy(&a, &b, sizeof(foo));
}
