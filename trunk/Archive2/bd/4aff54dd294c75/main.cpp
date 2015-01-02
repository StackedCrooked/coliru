#include <type_traits>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Select type from list
template <unsigned int I, typename ...Ts>
struct items;

template <typename T, typename ...Ts>
struct items<0, T, Ts...>
{
    typedef T type;
};

template <unsigned int I, typename T, typename ...Ts>
struct items<I, T, Ts...> : items<I-1, Ts...>
{
};

template <unsigned int I>
struct items<I>
{
    typedef int type;
};

template <unsigned int I, typename ...Ts>
typename items<I, Ts...>::type get_item_selector();

template <unsigned int I, typename ...Ts>
using get_item = decltype(get_item_selector<I, Ts...>());

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Apply a single type parameter to a template, producing a new template
template<template<typename...> class TT, typename T>
struct apply_partial {
   template<typename... Ts>
   using type = TT<T, Ts...>;
};

// Apply parameters from I upto N, one after another, using apply_partial
template<template<typename...> class TT, std::size_t I, std::size_t N, typename... Ts>
struct apply_seq {
   typedef typename apply_seq<
         apply_partial<TT, get_item<I, Ts...>>::template type,
         I+1, N, Ts...
      >::type type;
};

template<template<typename...> class TT, std::size_t N, typename... Ts>
struct apply_seq<TT, N, N, Ts...> {
   typedef TT<> type;
};

// Main template
template<template<typename...> class TT, std::size_t N, typename... Ts>
using template_with_params = typename apply_seq<TT, 0, N, Ts...>::type;


// Tests:

template <typename... Ts>
struct B {};

int main()
{
    template_with_params<B, 3, int>{};
    static_assert(std::is_same< template_with_params<B, 3, int>, 
                                B<int,void,void>  >{}, "!");
    static_assert(std::is_same< template_with_params<B, 1, int, float, char>, 
                                B<int>  >{}, "!");
                                
    static_assert(std::is_same< template_with_params<B, 3, int, float, char, double>,
                               B<int, float, char>  >{}, "!");
}
