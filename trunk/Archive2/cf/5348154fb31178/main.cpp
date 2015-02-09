#include <cstddef>
#include <iostream>

template<typename T, std::size_t N>
struct array 
{
    array<T, N - 1> values;
    T value;
};

template<typename T>
struct array<T, 0> {};

template<std::size_t Idx, std::size_t N, typename T>
T& at(array<T, N>& arr)
{
    if (Idx == N - 1)
        return arr.value;
    else
        return at<Idx>(arr.values);
}

template<std::size_t Idx, typename T>
T& at(array<T, 0>&);


int main()
{
    array<int, 3> my_array = { {{{}, 1}, 2}, 3 };

    std::cout << at<0>(my_array) << "\n";
    std::cout << at<1>(my_array) << "\n";
    std::cout << at<2>(my_array) << "\n";
}
