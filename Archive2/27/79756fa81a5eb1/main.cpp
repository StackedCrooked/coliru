#include <tuple>
#include <iostream>
#include <utility>

template <typename T, std::size_t... indices, class tuple_t = std::decay_t<T>, size_t tuple_size = std::tuple_size<tuple_t>{}, class ret_type=std::tuple<std::tuple_element_t<tuple_size - indices - 1, tuple_t>...>>
ret_type invert( T&& tuple, std::index_sequence<indices...> )
{
    return ret_type ( std::get<tuple_size - indices - 1>(std::forward<T>(tuple))... );
}

template <typename T>
auto invert( T&& tuple )
{
    return invert( std::forward<T>(tuple),
                   std::make_index_sequence<std::tuple_size<std::decay_t<T>>{}>() );
}


int main()
{
	std::tuple<char, int, std::string> tup('4', 2, "asdf");
	auto result = invert(tup);
	std::cout << std::get<0>(result) << ' ' << std::get<1>(result) << ' ' << std::get<2>(result);
}
