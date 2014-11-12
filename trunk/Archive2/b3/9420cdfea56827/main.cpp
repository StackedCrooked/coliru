#include <cstdlib>

constexpr auto Length(const char *str) {
    std::size_t ret{};
    for (; *str; ++str) {
        ++ret;
    }
    
    return ret;
}

int main() {
    static_assert(Length("abc") == 3);   
    static_assert(Length("") == 0);
}