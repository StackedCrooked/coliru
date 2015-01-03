template <int...> struct PossibleActions {};

using TwoAndThree = PossibleActions<2,3>;

template <typename, typename, int...> struct merge;
template <int... Ks> struct merge<PossibleActions<>, PossibleActions<>, Ks...> { using type = PossibleActions<Ks...>; };
template <int... Is, int... Ks> struct merge<PossibleActions<Is...>, PossibleActions<>, Ks...> { using type = PossibleActions<Ks..., Is...>; };
template <int... Js, int... Ks> struct merge<PossibleActions<>, PossibleActions<Js...>, Ks...> { using type = PossibleActions<Ks..., Js...>; };

template <bool, typename, typename, int...>
struct strip;

template <int I, int... Is, int J, int... Js, int... Ks>
struct strip<true, PossibleActions<I, Is...>, PossibleActions<J, Js...>, Ks...>
{
    using type = merge<PossibleActions<I, Is...>, PossibleActions<Js...>, Ks..., J>;
};

template <int I, int... Is, int J, int... Js, int... Ks>
struct strip<false, PossibleActions<I, Is...>, PossibleActions<J, Js...>, Ks...>
{
    using type = merge<PossibleActions<Is...>, PossibleActions<J, Js...>, Ks..., I>;
};

template <int I, int... Is, int J, int... Js, int... Ks>
struct merge<PossibleActions<I, Is...>, PossibleActions<J, Js...>, Ks...>
    : strip<(I>J), PossibleActions<I, Is...>, PossibleActions<J, Js...>, Ks...>::type {};

#include <type_traits>
#include <iostream>

template <typename T> void TD() { std::cout << __PRETTY_FUNCTION__ << std::endl; }

int main()
{
    static_assert(std::is_same<merge<PossibleActions<1, 4>, TwoAndThree>::type, PossibleActions<1, 2, 3, 4>>{}, "!");
}
