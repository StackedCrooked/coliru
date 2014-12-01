#include <utility>
#include <tuple>

template <class T, class=std::make_index_sequence<std::tuple_size<T>::value-1>>
struct pop;

template <typename... Ts, std::size_t... indices>
struct pop<std::tuple<Ts...>, std::index_sequence<indices...>>
{
    using type = std::tuple<std::tuple_element_t<indices, std::tuple<Ts...>>...>;
};

template <typename T>
using pop_t = typename pop<T>::type;

using t = std::tuple<int, char, float>;
static_assert( std::is_same<pop_t<t>, std::tuple<int, char>>{}, "" );

int main() {}
