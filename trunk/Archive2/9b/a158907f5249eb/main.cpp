#include <type_traits>

namespace detail
{
    template <typename T, typename, typename, T...> struct merge;
    template <typename T, template <T...> class S, T... Ks> struct merge<T, S<>, S<>, Ks...> { using type = S<Ks...>; };
    template <typename T, template <T...> class S, T... Is, T... Ks> struct merge<T, S<Is...>, S<>, Ks...> { using type = S<Ks..., Is...>; };
    template <typename T, template <T...> class S, T... Js, T... Ks> struct merge<T, S<>, S<Js...>, Ks...> { using type = S<Ks..., Js...>; };
    template <typename T, bool, typename, typename, T...> struct strip;
    template <typename T, template <T...> class S, T I, T... Is, T J, T... Js, T... Ks>
    struct strip<T, true, S<I, Is...>, S<J, Js...>, Ks...> { using type = merge<T, S<I, Is...>, S<Js...>, Ks..., J>; };
    template <typename T, template <T...> class S, T I, T... Is, T J, T... Js, T... Ks>
    struct strip<T, false, S<I, Is...>, S<J, Js...>, Ks...> { using type = merge<T, S<Is...>, S<J, Js...>, Ks..., I>; };
    template <typename T, template <T...> class S, T I, T... Is, T J, T... Js, T... Ks>
    struct merge<T, S<I, Is...>, S<J, Js...>, Ks...> : strip<T, (I>J), S<I, Is...>, S<J, Js...>, Ks...>::type {};
}
template <typename A, typename B> using merge = typename detail::merge<int, A, B>::type;

template <int...> struct seq {};

int main()
{
    static_assert(std::is_same<merge<seq<1, 3, 4, 7>, seq<0, 2, 5, 6>>, seq<0, 1, 2, 3, 4, 5, 6, 7>>{}, "!");
}
