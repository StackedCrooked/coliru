#include <utility>
#include <iostream>
#include <tuple>

template <typename Function,
          typename... T,
          std::size_t... indices>
void for_each( std::tuple<T...> const& t, Function f, std::index_sequence<indices...> )
{
    (void)std::initializer_list<int>{ (f(std::get<indices>(t)), 0)... };
}

template <typename Function,
          typename... T>
void for_each( std::tuple<T...> const& t, Function f )
{
	return for_each( t, f, std::make_index_sequence<sizeof...(T)>() );
}

int main()
{
	auto i = std::make_tuple(1, "aef", 5.8);
	for_each(i, [] (auto&& v) {std::cout << v << ' ';});
}
