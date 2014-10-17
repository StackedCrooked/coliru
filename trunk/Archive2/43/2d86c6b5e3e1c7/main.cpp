#include <tuple>

template <typename T, std::size_t counter = 0, typename... A> struct find_;
template <typename T, typename F, typename... Tail, std::size_t counter>
struct find_<T, counter, F, Tail...> : find_<T, counter+1, Tail...> {};
template <typename T, typename... Tail, std::size_t counter>
struct find_<T, counter, T, Tail...> : std::integral_constant<std::size_t, counter> {};

template <typename T, typename... Args>
using find = find_<T, 0, Args...>;

template< class T, class... Types >
T&& get(std::tuple<Types...>&& t)
{
    return std::get<find<T, Types...>::value>(std::move(t));
}

template< class T, class... Types >
T const& get(std::tuple<Types...> const& t)
{
	return std::get<find<T, Types...>::value>(t);
}

template< class T, class... Types >
T& get(std::tuple<Types...>& t)
{
	return std::get<find<T, Types...>::value>(t);
}

#include <iostream>

int main()
{
	auto myTuple = std::make_tuple("awef", 'e', 454);
	std::cout << get<int>(myTuple) << '\n';
	std::cout << get<char const*>(myTuple) << '\n';
	std::cout << get<char>(myTuple) << '\n';
}
