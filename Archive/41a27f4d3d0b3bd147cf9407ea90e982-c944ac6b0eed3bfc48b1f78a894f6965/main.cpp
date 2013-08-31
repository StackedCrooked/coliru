#include <cstddef>

template <int... I> struct indices {};
template <int N, int... I> struct make_indices : make_indices<N-1,N-1,I...> {};
template <int... I> struct make_indices<0,I...> : indices<I...> {};

#include <array>

template <std::size_t N, typename T, int... I>
std::array<T, N> array_maker(T t, indices<I...>)
{
    return std::array<T, N>{ ((void)I, t)... };
}


template <std::size_t N, typename T>
std::array<T, N> array_maker(T t)
{
    return array_maker<N>(t, make_indices<N>());
}

#include <iostream>

template <typename T, std::size_t N>
std::ostream& operator << (std::ostream& os, const std::array<T, N>& array) {
    os << "{ ";
    bool first = true;
    for (auto& i : array) {
        if (first)
            first = false;
        else
            os << ", ";
        os << i;
    }
    os << " }";
    return os;
}

int main() {
    auto a = array_maker<5>(42);
    std::cout << a << std::endl;
}