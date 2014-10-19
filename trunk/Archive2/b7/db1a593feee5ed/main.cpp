#include <iostream>
#include <tuple>
#include <type_traits>
#include <utility>
#include <cstddef>

template <std::size_t... Is>
struct index_sequence {};

template <std::size_t N, std::size_t... Is>
struct make_index_sequence_h : make_index_sequence_h<N - 1, N - 1, Is...> {};

template <std::size_t... Is>
struct make_index_sequence_h<0, Is...>
{
    using type = index_sequence<Is...>;
};

template <std::size_t N>
using make_index_sequence = typename make_index_sequence_h<N>::type;

template <std::size_t DIM, typename T>
class linear_searchspace
{
public:
    template <typename... Ts>
    inline constexpr auto operator()(Ts... args) const noexcept(std::is_nothrow_copy_constructible<T>::value)
        -> std::tuple<decltype(args, void(), T{})...>
    {
        static_assert(sizeof...(Ts) == DIM, "!");
        using Tuple = std::tuple<decltype(args, void(), T{})...>;
        return go<Tuple>(make_index_sequence<sizeof...(Ts)>{}, args...);
    }

private:
    template <typename Tuple, typename... Ts, std::size_t... Is>
    inline constexpr Tuple go(index_sequence<Is...>, Ts... args) const noexcept(std::is_nothrow_copy_constructible<T>::value)
    {
        return Tuple((some_kinda_structure[args] + Is)...);
    }

    T some_kinda_structure[DIM] = { 0, 1, 2, 3, 4 };
};

int main()
{
    linear_searchspace<5, int> lsp{};
    auto t = lsp(0, 1, 2, 3, 4);
    std::cout << std::get<1>(t) << std::endl;

    auto t2 = lsp(4, 3, 2, 1, 0);
    std::cout << std::get<0>(t2) << std::endl;
}
