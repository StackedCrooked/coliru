#include <type_traits>

struct a {
    a() = default;
    a(const a&) = delete;
};

int main() {
    static_assert(std::is_move_constructible<a>(), "..");
}