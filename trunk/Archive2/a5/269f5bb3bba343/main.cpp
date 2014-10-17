#include <cstddef>
#include <iostream>
#include <type_traits>
#include <tuple>
#include <stdexcept>

template<size_t... Indices>
struct indices {};

template<size_t N, size_t... Indices>
struct build_indices : build_indices<N-1, N-1, Indices...> {};

template<size_t... Indices>
struct build_indices<0, Indices...> : indices<Indices...> {};

// visitors
struct printer {
    template<typename T>
    void operator()(T&& t) const {
        std::cout << std::forward<T>(t);
    }
};

template<typename T>
struct extractor {
private:
    T& val;
public:
    extractor(T& val): val(val) {}

    template<typename U, typename std::enable_if<std::is_constructible<T, U>::value, int>::type = 0>
    void operator()(U&& t) const noexcept {
        val = std::forward<U>(t);
    }

    template<typename U, typename std::enable_if<!std::is_constructible<T, U>::value, int>::type = 0>
    void operator()(U&&) const noexcept {}
};

template<typename T>
inline extractor<T> make_extractor(T& t) {
    return { t };
}

// actual 'visitation' based on runtime-index
template<typename Tuple, typename Function>
inline void apply_impl(const Tuple&, size_t, const Function&, indices<>) {
    throw std::out_of_range("tuple index is out of bounds");
}

template<size_t N, size_t... Tail, typename Tuple, typename Function>
inline void apply_impl(const Tuple& tuple, size_t index, const Function& f, indices<N, Tail...>) {
    if(index == N) {
        f(std::get<N>(tuple));
    }
    else {
        apply_impl(tuple, index, f, indices<Tail...>{});
    }
}

template<typename Tuple, typename Function>
inline void apply(const Tuple& tuple, size_t index, const Function& f) {
    apply_impl(tuple, index, f, build_indices<std::tuple_size<Tuple>::value>{});
}

// demo
int main() {
    auto x = std::make_tuple(10, 11, "hello", "world");
    apply(x, 2, printer{});
    size_t y = 0;
    apply(x, 1, make_extractor(y));
    std::cout << '\n' << y << '\n';
}