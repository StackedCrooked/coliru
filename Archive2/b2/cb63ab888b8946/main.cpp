#include <tuple>
#include <type_traits>
#include <utility>
#include <iostream>

/* ========== Coliru doesn't have std::index_sequence or std::make_index_sequence yet =============== */

template <std::size_t... Indices>
struct index_sequence {
    typedef index_sequence<Indices..., sizeof...(Indices)> next;
};
 
template <std::size_t Start>
struct make_index_sequence {
    typedef typename make_index_sequence<Start - 1>::type::next type;
};
 
template <>
struct make_index_sequence<0> {
    typedef index_sequence<> type;
};
 
template <int n>
using make_index_sequence_t = typename make_index_sequence<n>::type;

/* =============================================================================== */

template<class Function, class Tuple, size_t... I>
auto tuple_map_impl(Function f, Tuple&& t, index_sequence<I...>)
{
    return std::make_tuple(
        f(std::get<I>(std::forward<Tuple>(t)))...
    );
}

template <class F, class Tuple, class... Tuples>
auto tuple_map(F f, Tuple&& t, Tuples&&... tuples)
{
    return std::tuple_cat(tuple_map_impl(f, std::forward<Tuple>(t), make_index_sequence_t<std::tuple_size<std::decay_t<Tuple>>::value>{}),
                          tuple_map(f, tuples...)
           );
}

template <class F>
auto tuple_map(F) { return std::make_tuple(); }

/* ================= Test =================== */

template <class Tuple, std::size_t... I>
void print(Tuple&& t, index_sequence<I...>)
{
    auto l = {0, ((std::cout << std::get<I>(t) << " "), 0)...};
    (void)l;
}

template <class Tuple>
void print(Tuple&& t)
{
    print(t, make_index_sequence_t<std::tuple_size<std::decay_t<Tuple>>::value>{});
}

int main()
{
    auto t = std::make_tuple(1, 2, 3);
    std::cout << "Before: "; print(t); std::cout << std::endl;
    
    auto f = [] (int n) { return n*10; };
    auto result = tuple_map(f, t);
    
    std::cout << "After: ";
    print(result);
}