template <int...> struct seq {};
template <int N, int... Is> struct gen_seq : gen_seq<N - 1, N - 1, Is...> {};
template <int... Is> struct gen_seq<0, Is...> { using type = seq<Is...>; };
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
struct merge<T, S<I, Is...>, S<J, Js...>, Ks...> : strip<T, (I > J), S<I, Is...>, S<J, Js...>, Ks...>::type {};
template <int N, typename T, T...> struct get;
template <int N, typename T, T I, T... Is>
struct get<N, T, I, Is...> : get<N - 1, T, Is...> {};
template <typename T, T I, T... Is>
struct get<0, T, I, Is...> { static constexpr T value = I; };
template <typename, typename, typename = void, typename = void> struct sort;
template <typename T, template <T...> class S, int... L, int... R, T... Is>
struct sort<T, S<Is...>, seq<L...>, seq<R...>> : merge<T, typename sort<T, S<get<L, T, Is...>::value...>>::type, typename sort<T, S<get<sizeof...(L) + R, T, Is...>::value...>>::type> {};
template <typename T, template <T...> class S, T... Is>
struct sort<T, S<Is...>, void, void> : sort<T, S<Is...>, typename gen_seq<sizeof...(Is) / 2>::type, typename gen_seq<sizeof...(Is) - sizeof...(Is) / 2>::type> {};
template <typename T, T I, template <T...> class S> struct sort<T, S<I>, seq<0>, seq<>> { using type = S<I>; };
template <typename T, T I, template <T...> class S> struct sort<T, S<I>, seq<>, seq<0>> { using type = S<I>; };

#include <type_traits>
int main()
{
    static_assert(std::is_same<sort<int, seq<5, 9, 8, 3, 4, 2, 7, 1, 6>>::type, seq<1, 2, 3, 4, 5, 6, 7, 8, 9>>{}, "!");
}
