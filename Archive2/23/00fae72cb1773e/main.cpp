#include <cassert>
#include <tuple>
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
    constexpr linear_searchspace(Ts&&... ts) : some_kinda_structure{ std::forward<Ts>(ts)... }
    {
        static_assert(sizeof...(Ts) == DIM, "wrong number of elements!");
    }

    template <typename... Args>
    inline constexpr auto operator()(Args... args) const
        noexcept(noexcept(T{std::declval<T>()}))
        -> std::tuple<decltype((void)args, T{std::declval<T>()})...>
    {
        static_assert(sizeof...(Args) == DIM, "wrong number of indices!");
        using Tuple = std::tuple<decltype((void)args, T{std::declval<T>()})...>;
        return get<Tuple>(make_index_sequence<sizeof...(Args)>{}, args...);
    }

private:
    template <typename Tuple, typename... Args, std::size_t... Is>
    inline constexpr Tuple get(index_sequence<Is...>, Args... args) const
        noexcept(noexcept(T{std::declval<T>()}))
    {
        return Tuple((some_kinda_structure[args] + Is)...);
        //                                       ^^^^
        // some calculation for each element based on index (here simple addition)
    }

    T some_kinda_structure[DIM]; // implementation defined
};

int main()
{
    constexpr linear_searchspace<5, int> lsp{ 1, 2, 3, 4, 5 };

    // evaluated at compile-time
    constexpr auto t = lsp(0, 1, 2, 3, 4);
    static_assert(std::get<1>(t) == 3, "!");

    // evaluated at run-time
    auto t2 = lsp(4, 3, 2, 1, 0);
    assert(std::get<3>(t2) == 5);
}
