#include <cstddef>
#include <utility>
#include <type_traits>
#include <tuple>

template <template <typename...> class T, typename D, std::size_t N, typename... Ts>
struct template_with_params_impl;

template <template <typename...> class T, typename D, std::size_t N, std::size_t... Is, std::size_t... Js, typename... Ts>
struct template_with_params_impl<T, D, N, std::index_sequence<Is...>, std::index_sequence<Js...>, Ts...>
{
    using type = T<typename std::tuple_element<Is, std::tuple<Ts...>>::type..., typename std::remove_reference<decltype(void(Js), std::declval<D>())>::type...>;
};

template <bool B, template <typename...> class T, typename D, std::size_t N, typename... Ts>
struct template_with_params_c
{
    using type = template_with_params_impl<T, D, N, std::make_index_sequence<N>, std::make_index_sequence<0>, Ts...>;
};

template <template <typename...> class T, typename D, std::size_t N, typename... Ts>
struct template_with_params_c<false, T, D, N, Ts...>
{
    using type = template_with_params_impl<T, D, N, std::make_index_sequence<sizeof...(Ts)>, std::make_index_sequence<N - sizeof...(Ts)>, Ts...>;
};

template <template <typename...> class T, typename D, std::size_t N, typename... Ts>
using template_with_params = typename template_with_params_c<(sizeof...(Ts) >= N), T, D, N, Ts...>::type::type;

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
