#include <tuple>
#include <utility>
#include <cassert>

template <class... T, std::size_t... i>
auto to_tuple_ref_helper(std::tuple<T...>& t, std::index_sequence<i...>) {
    return std::tuple<T&...> {std::get<i>(t)...};
}

template <class... T>
auto to_tuple_ref(std::tuple<T...>& t) {
    return to_tuple_ref_helper(t, std::make_index_sequence<sizeof...(T)>());
}

template <class T>
auto to_tuple_ref(T& t) {
    return std::tuple<T&>{t};
}

template <class... Ts>
auto flattening_tie(Ts &...args) {
    return std::tuple_cat(to_tuple_ref(args)...);
}

int main() {
    std::tuple<int, char> a;
    std::tuple<double> b;
    float c;
    flattening_tie(a, b, c, std::ignore) = std::make_tuple(10, 'a', 3.0, 1.0f, "test");
    
    assert(a == std::make_tuple(10, 'a'));
    assert(b == std::make_tuple(3.0));
    assert(c == 1.0f);
}