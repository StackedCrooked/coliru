#include <iostream>
#include <type_traits>
#include <utility>
 
template <class... T> struct pack {
    using type = pack;
    static constexpr auto size = sizeof...(T);
};

namespace detail {
    template <std::size_t, class result, class>
    struct accumulator : result {};
    
    template <std::size_t j, class... R, class T1, class... T>
    struct accumulator<j, pack<R...>, pack<T1, T...>> :
        std::conditional_t<j&1, accumulator<(j>>1), pack<R..., T1>, pack<T...>>,
                                accumulator<(j>>1), pack<R...    >, pack<T...>>> {};
}

template <class P, class=std::make_index_sequence<1ull << P::size>> struct power_pack;
template <class P, std::size_t... indices>
struct power_pack<P, std::index_sequence<indices...>> :
    pack<typename detail::accumulator<indices, pack<>, P>::type...>{};
    
template <typename... T>
void print(pack<T...>) {std::cout << __PRETTY_FUNCTION__ << '\n';}
 
int main() {
    using type = power_pack<pack<int, double, float>>::type;
    print(type{});
}