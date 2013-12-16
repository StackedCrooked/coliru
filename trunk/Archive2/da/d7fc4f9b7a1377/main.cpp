#include <tuple>

auto f(std::tuple<>) -> int;

template<typename H, typename... T>
auto f(std::tuple<H, T...>) -> decltype(f(std::tuple<T...>()));

int main() {
    f(std::make_tuple(1, 1, 1));
}
