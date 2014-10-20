#include <cassert>
#include <tuple>
#include <utility>
#include <cstddef>
#include <array>

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
    constexpr linear_searchspace(const std::array<T, DIM>& a) : some_kinda_structure(a) {}

    template <typename... Ts>
    inline constexpr auto operator()(Ts... args) const
        noexcept(noexcept(T{std::declval<T>()}))
        -> std::tuple<decltype((void)args, T{std::declval<T>()})...>
    {
        static_assert(sizeof...(Ts) == DIM, "wrong number of indices!");
        using Tuple = std::tuple<decltype((void)args, T{std::declval<T>()})...>;
        return get<Tuple>(make_index_sequence<sizeof...(Ts)>{}, args...);
    }

private:
    template <typename Tuple, typename... Ts, std::size_t... Is>
    inline constexpr Tuple get(index_sequence<Is...>, Ts... args) const
        noexcept(noexcept(T{std::declval<T>()}))
    {
        return Tuple((some_kinda_structure[args] + Is)...);
        //                                       ^^^^
        // some calculation for each element based on index (here simple addition)
    }

    std::array<T, DIM> some_kinda_structure; // implementation defined
};

int main()
{
    constexpr linear_searchspace<5, int> lsp{ { 1, 2, 3, 4, 5 } };

    // evaluated at compile-time
    constexpr auto t = lsp(0, 1, 2, 3, 4);
    static_assert(std::get<1>(t) == 3, "!");

    // evaluated at run-time
    auto t2 = lsp(4, 3, 2, 1, 0);
    assert(std::get<3>(t2) == 5);
}
