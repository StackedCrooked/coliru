#include <type_traits>
#include <tuple>

//-----------------------------------------------------------------------------

template <typename T, T... N>
struct integrals { using type = integrals <T, N...>; };

//-----------------------------------------------------------------------------

template <typename... I> struct join_t;
template <typename... I> using  join = typename join_t <I...>::type;

template <typename T, T... L, T... R, typename... I>
struct join_t <integrals <T, L...>, integrals <T, R...>, I...> :
    join_t <integrals <T, L..., R...>, I...> { };

template <typename T, T... N>
struct join_t <integrals <T, N...> > : integrals <T, N...> { };

//-----------------------------------------------------------------------------

template <typename T, T B, T L, typename = integrals <T, L> >
struct range_impl_t;

template <typename T, T B, T L>
using range_impl = typename range_impl_t <T, B, L>::type;

template <typename T, T B, T L, typename>
struct range_impl_t :
	join <range_impl <T, B, L/2>, range_impl <T, B + L/2, (L+1)/2> > { };

template <typename T, T B, T L>
struct range_impl_t <T, B, L, integrals <T, 0> > : integrals <T> { };

template <typename T, T B, T L>
struct range_impl_t <T, B, L, integrals <T, 1> > : integrals <T, B> { };

template <typename T, T L>
using range_t = typename std::conditional <(L < 0),
	integrals <T>, range_impl <T, 0, L>
>::type;

template <typename T, T L>
using range = typename range_t <T, L>::type;

//-----------------------------------------------------------------------------

template <typename R>
struct List_impl;

template <int... N>
struct List_impl <integrals <int, N...> >
{
	using type = std::tuple <std::integral_constant <int, N>...>;
};

template <int N>
using List = typename List_impl <range <int, N> >::type;

//-----------------------------------------------------------------------------

int main ()
{
	List <100>::dummy();
}
