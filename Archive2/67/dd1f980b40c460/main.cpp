#include <cstddef>
#include <utility>
#include <type_traits>
#include <tuple>

template <std::size_t... Is>
struct index_sequence {};

template <std::size_t N, std::size_t... Is>
struct make_index_sequence_h : make_index_sequence_h<N - 1, N - 1, Is...> {};

template <std::size_t... Is>
struct make_index_sequence_h<0, Is...> { using type = index_sequence<Is...>; };

template <std::size_t N>
using make_index_sequence = typename make_index_sequence_h<N>::type;

template <template <typename...> class T, typename D, std::size_t N, typename... Ts>
struct template_with_params_impl;

template <template <typename...> class T, typename D, std::size_t N, std::size_t... Is, std::size_t... Js, typename... Ts>
struct template_with_params_impl<T, D, N, index_sequence<Is...>, index_sequence<Js...>, Ts...>
{
    using type = T<typename std::tuple_element<Is, std::tuple<Ts...>>::type..., typename std::remove_reference<decltype(void(Js), std::declval<D>())>::type...>;
};

template <template <typename...> class T, typename D, std::size_t N, typename... Ts>
using template_with_params = typename template_with_params_impl<T, D, N, make_index_sequence<sizeof...(Ts) >= N ? N : sizeof...(Ts)>, make_index_sequence<sizeof...(Ts) >= N ? 0 : N - sizeof...(Ts)>, Ts...>::type;

// Tests:
#include <iostream>
template <typename... Ts>
struct B { void foo() { std::cout << 1; } };

int main()
{    
    template_with_params<B, void, 3, int> b{}; b.foo();
    
    static_assert(std::is_same< template_with_params<B, void, 3, int>, 
                                B<int, void, void>  >{}, "!");
                                
    static_assert(std::is_same< template_with_params<B, void, 1, int, float>, 
                                B<int>  >{}, "!");
}
