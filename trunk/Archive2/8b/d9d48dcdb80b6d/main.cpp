#include <iostream>
#include <tuple>

template <std::size_t I, std::size_t N, typename F, typename T>
struct transform_tuple_helper {
    template <typename... Accum>
    static auto
    do_(F f, T t, Accum... accum)
        -> decltype(transform_tuple_helper<I + 1, N, F, T>::do_(f, t, accum..., f(std::get<I>(t))))
    {
        return transform_tuple_helper<I + 1, N, F, T>::do_(f, t, accum..., f(std::get<I>(t)));
    }
};

template <std::size_t N, typename F, typename T>
struct transform_tuple_helper<N, N, F, T> {
    template <typename... Accum>
    static auto
    do_(F, T, Accum... accum) 
        -> decltype(std::make_tuple(accum...))
    {
        return std::make_tuple(accum...);
    }
};

template <typename F, typename T>
auto
transform_tuple(T t, F f) 
    -> decltype(transform_tuple_helper<0, std::tuple_size<T>::value, F, T>::do_(f, t))
{
    return transform_tuple_helper<0, std::tuple_size<T>::value, F, T>::do_(f, t);
}


struct doubler {
    template <typename T>
    double
    operator () (T x) {
        return 2 * x + 0.1;
    }
};

int
main() {
    
    std::tuple<int, double> a{5, 7.2};
    std::tuple<double, double> b = transform_tuple(a, doubler{});
    std::cout << std::get<0>(b) << ", " << std::get<1>(b) << '\n';
}
