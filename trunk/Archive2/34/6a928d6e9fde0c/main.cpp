#include <cstddef>
#include <tuple>
#include <utility>

template <template <typename...> class T, std::size_t N, typename Seq, typename... Ts>
struct template_with_params_impl;

template <template <typename...> class T, std::size_t N, std::size_t... Is, typename... Ts>
struct template_with_params_impl<T, N, std::index_sequence<Is...>, Ts...>
{
    using type = T<typename std::tuple_element<Is, std::tuple<Ts...>>::type...>;
};

template <template <typename...> class T, std::size_t N, typename... Ts>
using template_with_params = template_with_params_impl<T, N, std::make_index_sequence<N>, Ts...>;

// Tests:
#include <type_traits>

template <typename... Ts>
struct B {};

int main()
{
    static_assert(std::is_same<  template_with_params<B, 1, int, float, char>::type, B<int>  >{}, "!");
    static_assert(std::is_same<  template_with_params<B, 3, int, float, char, double>::type, B<int, float, char>  >{}, "!");
}
