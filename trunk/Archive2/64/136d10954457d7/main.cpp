#include <iostream>
#include <utility>
#include <tuple>

template <class T> struct identity {using type = T;};

template <typename> struct sizeof_pack;
template <template<class...> class Tm,  typename... T>
struct sizeof_pack<Tm<T...>> : std::integral_constant<std::size_t, sizeof...(T)> {};

struct empty_tag;

template <typename T, typename...> struct clean : identity<T> {};
template <typename... cur, typename T, typename... Ts>
struct clean<std::tuple<cur...>, T, Ts...> : clean<std::tuple<cur..., T>, Ts...> {};
template <typename... cur, typename... Ts>
struct clean<std::tuple<cur...>, empty_tag, Ts...> : clean<std::tuple<cur...>, Ts...> {};

template <std::size_t, typename, typename=void> struct get_elem;
template <std::size_t i, template<typename...> class tmpl,
          typename... T>
struct get_elem<i, tmpl<T...>>
    : std::tuple_element<(i < sizeof...(T))*(i+1), std::tuple<empty_tag, T...>> {};

template <typename, std::size_t, std::size_t, typename...>
struct interlace_impl;
template <typename... r, std::size_t N, std::size_t i, typename ... packs>
struct interlace_impl<std::tuple<r...>, N, i, packs...> :
    interlace_impl<std::tuple<r..., typename get_elem<i, packs>::type...>, N, i+1, packs...> {};
template <typename... r, std::size_t N, typename ... packs>
struct interlace_impl<std::tuple<r...>, N, N, packs...> :
    clean<std::tuple<>, r...> {};

template <typename... packs>
using sizeof_largest = std::integral_constant<std::size_t, std::max({sizeof_pack<packs>::value...})>;
template <typename ... packs>
using interlace = interlace_impl<std::tuple<>, sizeof_largest<packs...>{}, 0, packs...>;

/// TEST:

template <typename T> void print () {std::cout << __PRETTY_FUNCTION__;}

template <typename...> struct Pack {};
template <typename...> struct Group {};
template <typename...> struct Wrap {};
struct Object {};  struct Blob {};

using TestPack1 = Pack<int, double, Object>;  // 3 types
using TestPack2 = Group<double, char, int, short, long>;  // 5 types
using TestPack3 = Wrap<char, short, Blob, char>;  // 4 types

int main()
{
    print<interlace<TestPack1, TestPack2, TestPack3>::type>();
}