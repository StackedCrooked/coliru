#include <cstddef>

template<typename T, std::size_t N>
struct array : array<T, N - 1>
{
    T value;
};

template<typename T>
struct array<T, 0> {};

template<std::size_t Idx, std::size_t N, typename T>
T& at(array<T, N>& arr)
{
    return static_cast<array<T, Idx + 1>&>(arr).value;
}

int main()
{
    array<int, 3> my_array;

    at<0>(my_array) = 1;
    at<1>(my_array) = 2;
    at<2>(my_array) = 3;
}
