#include <algorithm>
#include <array>
#include <type_traits>

template<typename F>
auto foo(F f) -> std::array<decltype(f()), 5> {
    std::array<decltype(f()), 5> ret;
    std::fill(std::begin(ret), std::end(ret), f());
    return ret;
}

int fa() {
    return 1;
}

std::array<int, 1> fb() {
    return std::array<int, 1>{{2}};
}

int main() {
    auto a = foo(fa);
    auto b = foo(fb);
    
    static_assert(std::is_same<decltype(a), std::array<int, 5>>::value, "a");
    static_assert(std::is_same<decltype(b), std::array<std::array<int, 1>, 5>>::value, "b");
}