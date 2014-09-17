#include <array>
#include <cmath>
#include <iostream>

template<typename T, std::size_t N>
auto norm(const std::array<T, N>& arr)
    -> T
{
    T res{};
    for (auto value: arr)
    {
        res += value * value;
    }
    return std::sqrt(res);
}

int main()
{
    std::array<double, 3u> arr = { 4.0, -2.0, 6.0 };
    std::cout << norm(arr) - norm(arr) << '\n';
}