#include <cstddef>

template <typename T, std::size_t N>
constexpr std::size_t size(T(&)[N]) {
    return N;
}

int main() {
    char16_t const s[] = u"U\00010000";
    static_assert(size(s) == 3, "s has three code units");
}