#include <iostream>
using namespace std;
namespace {

template<typename T>
constexpr auto f(T && t) noexcept {
    return true;
}

template<typename T>
constexpr auto f_helper(T && t) noexcept(noexcept(f(t))) {
    return f(t);
}

template<typename T, typename... Ts>
constexpr auto f_helper(T && t, Ts && ... ts) noexcept(noexcept(f(ts...))) {
    return f(ts...);
}

template<typename T, typename... Ts>
constexpr auto f(T && t, Ts && ... ts) noexcept(noexcept(f_helper(ts...))) {
    return f(ts...);
}

}   // namespace

int main() {
    f(true, 0, 5u, 3ul);
}