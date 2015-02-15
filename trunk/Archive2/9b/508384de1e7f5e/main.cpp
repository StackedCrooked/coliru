#include <iostream>
#include <tuple>
#include <utility>

template <typename TupleLike, size_t ... Inds>
std::ostream& PrintHelper(std::ostream& out, TupleLike const& tuple, std::index_sequence<Inds...>)
{
  int unused[] = {0, (out << std::get<Inds>(tuple) << " ", 0)...};
  (void)unused;
  return out;
}

template<typename... Types>
std::ostream& operator<<(std::ostream& out, std::tuple<Types...> const& tuple)
{
  return PrintHelper(out, tuple, std::make_index_sequence<sizeof...(Types)>());
}

int main()
{
    auto tuple = std::make_tuple(1, 2.3, "Hello");
    std::cout << tuple << std::endl;
    return 0;
}