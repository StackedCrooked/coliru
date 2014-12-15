#include <iostream>
#include <tuple>

template <std::size_t I, std::size_t N, typename F, typename T>
struct transform_tuple_helper {
    template <typename... Accum>
    static auto
    do_(F f, T t, Accum... accum) {
        return transform_tuple_helper<I + 1, N, F, T>::do_(f, t, accum..., f(std::get<I>(t)));
    }
};

template <std::size_t N, typename F, typename T>
struct transform_tuple_helper<N, N, F, T> {
    template <typename... Accum>
    static auto
    do_(F, T, Accum... accum) {
        return std::make_tuple(accum...);
    }
};

template <typename F, typename T>
auto
transform_tuple(T t, F f) {
    return transform_tuple_helper<0, std::tuple_size<T>::value, F, T>::do_(f, t);
}

int
main() {
    std::tuple<int, double> a{5, 7.2};
    std::tuple<int, double> b = transform_tuple(a, [] (auto x) { return 2 * x; });
    std::cout << std::get<0>(b) << ", " << std::get<1>(b) << '\n';
}
