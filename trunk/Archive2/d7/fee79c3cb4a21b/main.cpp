#include <bitset>
#include <cstddef>
#include <initializer_list>

#define FLAGS(t, ...) \
    enum class t { __VA_ARGS__, _count }

template<typename T, typename... Ts>
auto flags(T f, Ts... fs) {
    std::bitset<static_cast<std::size_t>(T::_count)> result;
    result[static_cast<std::size_t>(f)] = true;
    std::initializer_list<int> x{ ((result[static_cast<std::size_t>(fs)] = true), 0)... };
    (void)x;
    return result;
}

// example
#include <iostream>

FLAGS(Gender, Male, Female, Whale);

int main() {
    std::cout << flags(Gender::Male, Gender::Female) << '\n';
    std::cout << flags(Gender::Whale) << '\n';
    return 0;
}