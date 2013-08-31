#include <array>
#include <cstddef>
#include <algorithm>
#include <iostream>

template <typename T, std::size_t N>
std::array<T, N> operator +(std::array<T, N> lhs, std::array<T, N> const& rhs)
{
    /*auto j = rhs.cbegin();
    for(auto i = lhs.begin(); i != lhs.end(); ++i, ++j)
    {
        *i += *j;
    }*/
    std::transform(lhs.begin(), lhs.end(), rhs.begin(), lhs.begin(), std::plus<T>{});

    return lhs;
}

int main()
{
    std::array<int, 3> x{{1, 2, 3}}, y{{4, 5, 6}};

    auto result = x + y;

    for (auto const& e : result)
        std::cout << e << ' '; // 1 2 3 4 5 6
}
