#include <wheels/enums.h++>

#include <type_traits>

constexpr unsigned long long bit(int n) {
    return 1 << n;
}

enum class foo : int { a = bit(0), b = bit(1), c = bit(2) };

using bar = foo;

namespace wheels {
    template <> struct is_flags<bar> : std::true_type {};
}

constexpr foo foos[] = {
    bar::a | bar::b | bar::c
};

int main() {
}
