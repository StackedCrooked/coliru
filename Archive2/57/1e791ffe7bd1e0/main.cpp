#include <utility>
#include <cstddef>
#include <array>

struct Point
{
    template <typename... Ts>
    Point(Ts...) {}
};

template <typename PointT, std::size_t N, std::size_t... Is>
PointT to(std::array<double, N> const& a, std::index_sequence<Is...>)
{
    return PointT(a[Is]...);
}

template <typename PointT, std::size_t N>
PointT to(std::array<double, N> const& a)
{
    return to<PointT>(a, std::make_index_sequence<N>{});
}

int main()
{
    std::array<double, 3> a = { 1.0, 2.0, 3.0 };
    to<Point>(a);
}
