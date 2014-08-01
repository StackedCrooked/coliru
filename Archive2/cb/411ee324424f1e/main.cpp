#include <utility>
#include <array>
#include <tuple>

// Fill in missing stuff
namespace ersatz {

template<std::size_t I, typename T> using tuple_element_t = typename std::tuple_element<I, T>::type;
template<typename T> using remove_reference_t = typename std::remove_reference<T>::type;
template<typename... T> using common_type_t = typename std::common_type<T...>::type;

template<typename Int, Int... Seq> struct integer_sequence {
    using value_type = Int;
    static constexpr std::size_t size() noexcept { return sizeof...(Seq); }
};

template<std::size_t... Seq> using index_sequence = integer_sequence<std::size_t, Seq...>;

template<typename Int, std::size_t Acc, Int... Seq> struct build_sequence { using type = typename build_sequence<Int, Acc - 1, Acc - 1, Seq...>::type; };
template<typename Int, Int... Seq> struct build_sequence<Int, 0, Seq...> { using type = integer_sequence<Int, Seq...>; };

template<typename Int, Int N> using make_integer_sequence = typename build_sequence<Int, N>::type;
template<std::size_t N> using make_index_sequence = make_integer_sequence<std::size_t, N>;
    
} // ersatz

template<
    typename Tuple,
    typename VTuple = ersatz::remove_reference_t<Tuple>,
    std::size_t... Indices
>
constexpr std::array<
    ersatz::common_type_t<ersatz::tuple_element_t<Indices, VTuple>...>,
    sizeof...(Indices)
>
to_array(Tuple&& tuple, ersatz::index_sequence<Indices...>)
{
    return { std::get<Indices>(std::forward<Tuple>(tuple))... };
}

template<typename Tuple, typename VTuple = ersatz::remove_reference_t<Tuple>>
constexpr auto to_array(Tuple&& tuple)
{
    return to_array(
        std::forward<Tuple>(tuple),
        ersatz::make_index_sequence<std::tuple_size<VTuple>::value> {} );
}

int main()
{
    constexpr std::array<int, 3> a = { 1, 2, 3 };
    constexpr auto u = to_array(std::tuple_cat(a, a));
    constexpr auto e = u[4];
    return e;
}