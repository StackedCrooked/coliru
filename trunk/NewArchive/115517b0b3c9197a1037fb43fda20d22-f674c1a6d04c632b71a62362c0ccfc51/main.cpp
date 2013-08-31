#include <array>
#include <cstddef>
#include <algorithm>
#include <iostream>

template <typename T, std::size_t N0, std::size_t N1>
std::array<T, N0+N1> operator +(std::array<T, N0> const& lhs, std::array<T, N1> const& rhs)
{
    std::array<T, N0+N1> result;
    std::copy(std::begin(lhs), std::end(lhs), std::begin(result));
    std::copy(std::begin(rhs), std::end(rhs), std::begin(result)+N0);

    return result;
}

int main()
{
    std::array<int, 3> x{{1, 2, 3}}, y{{4, 5, 6}};

    auto result = x + y;

    for (auto const& e : result)
        std::cout << e << ' '; // 1 2 3 4 5 6
}
