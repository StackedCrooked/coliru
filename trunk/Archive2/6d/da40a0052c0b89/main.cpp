#include <iostream>
#include <cstdint>
#include <array>
#include <algorithm>
#include <iterator>

template <typename T, std::size_t N, std::size_t ...Indices>
struct make_array
{
    template <typename... Ts>
    auto operator ()(Ts ...ts)
    {
        std::array<T, N> ret{};
        int const _[]{ (ret[Indices] = ts, 0)... };
        static_cast<void>(_);
        return ret;
    }
};

int main()
{
    // int foo[] = { [0] = 1, [2] = 7, [9] = 42, [65] = -42 };
    auto foo(make_array<int, 66, 0, 2, 9, 65>{}(1, 7, 42, -42));
    std::copy(foo.begin(), foo.end(), std::ostream_iterator<int>(std::cout, " "));
}