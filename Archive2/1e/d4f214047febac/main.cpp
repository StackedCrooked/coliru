#include <cstddef>
#include <utility>
#include <type_traits>
template<bool...> struct foo {};
extern constexpr bool tab[3] = {true,false,true};

template<std::size_t N, const bool (&Tab)[N], class> struct ty1_helper;
template<std::size_t N, const bool (&Tab)[N], std::size_t... Is> struct ty1_helper<N, Tab, std::index_sequence<Is...>> { using type = foo<Tab[Is]...>; };

template<std::size_t N, const bool (&Tab)[N]>
using ty1 = typename ty1_helper<N, Tab, std::make_index_sequence<N>>::type;

constexpr bool tab2[3] = {true,false,true};
template<class> struct ty2_helper;
template<std::size_t... Is> struct ty2_helper<std::index_sequence<Is...>> { using type = foo<tab2[Is]...>; };

using ty2 = ty2_helper<std::make_index_sequence<3>>::type;

int main(){
    static_assert(std::is_same<ty1<3, tab>, foo<true, false, true>>::value, "Oops");
    static_assert(std::is_same<ty2, foo<true, false, true>>::value, "Oops");
}