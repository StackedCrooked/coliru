#include <iostream>
#include <type_traits>
#include <utility>
 
template <class... T> struct pack {
    using type = pack;
    static constexpr auto size = sizeof...(T);
};

template <unsigned j, class result, class input>
struct accumulator_impl {using type=result;};

template <unsigned j, class... R, class T1, class... T>
struct accumulator_impl<j, pack<R...>, pack<T1, T...>> :
    std::conditional_t<j&1, accumulator_impl<(j>>1), pack<R..., T1>, pack<T...>>,
                            accumulator_impl<(j>>1), pack<R...    >, pack<T...>>> {};
 
template <class P, class=std::make_index_sequence<1ull << P::size>> struct power_pack;
template <class P, std::size_t... indices>
struct power_pack<P, std::index_sequence<indices...>> :
    pack<typename accumulator_impl<indices, pack<>, P>::type...>{};
    
template <typename... T>
void print(pack<T...>) {std::cout << __PRETTY_FUNCTION__ << '\n';}
 
int main() {
    using type = power_pack<pack<int, double, float>>::type;
    print(type{});
}