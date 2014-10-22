#include <cstddef>
#include <utility>


template <typename ...Xs>
auto make_tuple(Xs&& ...xs) {
    // No perfect forwarding in the capture: maybe C++17?
    return [=](auto&& f) mutable -> decltype(auto) {
        return std::forward<decltype(f)>(f)(&xs...);
    };
}

template <std::size_t n, typename = std::make_index_sequence<n>>
struct get_impl;

template <std::size_t n, std::size_t ...ignore>
struct get_impl<n, std::index_sequence<ignore...>> {
    template <typename Nth>
    constexpr decltype(auto) operator()(decltype(ignore, (void const*)0)..., Nth nth, ...) const
    { return nth; }
};

template <std::size_t N, typename Tuple>
decltype(auto) get(Tuple& tuple) {
    return *tuple(get_impl<N>{});
}


#include <cassert>

int main() {
    auto xs = make_tuple('0', 1, 2.2);
    assert(get<0>(xs) == '0');
    assert(get<1>(xs) == 1);
    assert(get<2>(xs) == 2.2);

    get<2>(xs) = 2.2222222;
    assert(get<2>(xs) == 2.2222222);
}
