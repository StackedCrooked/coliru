#include <cstddef>
#include <tuple>

using std::size_t;

template <int... I> struct index_sequence {};
template <int N, int... I>
struct make_index_sequence : make_index_sequence<N-1,N-1,I...> {};
template <int... I>
struct make_index_sequence<0, I...> : index_sequence<I...> {};

template<typename T>
T getColumn(size_t i);

template<>
std::string getColumn<std::string>(size_t i) {
    if(i == 0)
        return "first";
    else
        return "other";
}

template<>
int getColumn<int>(size_t i) {
    return i*10;
}

template<typename... Values, int... I>
auto getColumns(index_sequence<I...>) ->
  decltype(std::make_tuple(getColumn<Values>(I)...)) {
    return std::make_tuple(getColumn<Values>(I)...);
}

template<typename... Values>
auto getColumns() ->
  decltype(getColumns<Values...>(make_index_sequence<sizeof...(Values)>())) {
    return getColumns<Values...>(make_index_sequence<sizeof...(Values)>());
}

#include <iostream>

int main() {
    auto v = getColumns<std::string, int, std::string, int>();
    std::cout << std::get<0>(v) << ' '
              << std::get<1>(v) << ' '
              << std::get<2>(v) << ' '
              << std::get<3>(v) << '\n';
}