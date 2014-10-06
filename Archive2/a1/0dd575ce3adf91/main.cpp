#include <iostream>
#include <algorithm>
#include <tuple>

// minimalistic index-list implementation

template <std::size_t...> struct index_list {using type = index_list;};

template <typename, typename> struct concat;
template <std::size_t... i, std::size_t... j>
struct concat<index_list<i...>, index_list<j...>> : index_list<i..., j...> {};

// Inefficient linear recursive definition of make_indices:
template <std::size_t N> struct make_indices :
    concat<typename make_indices<N-1>::type, index_list<N-1>> {};
template <> struct make_indices<0> : index_list<> {};
template <> struct make_indices<1> : index_list<0> {};

// </>

template <typename T, typename = typename make_indices<std::tuple_size<T>::value>::type> struct offsets;

template <typename... T, std::size_t... indices>
struct offsets<std::tuple<T...>, index_list<indices...>>
{
	static const std::tuple<T...> tuple;

	static char const* tuple_ptr;

	static constexpr void const* array[]
	{
		&std::get<indices>(tuple)...
	};
};

template <typename... T, std::size_t... indices>
constexpr void const* offsets<std::tuple<T...>, index_list<indices...>>::array[];
template <typename... T, std::size_t... indices>
const std::tuple<T...> offsets<std::tuple<T...>, index_list<indices...>>::tuple{};
template <typename... T, std::size_t... indices>
char const* offsets<std::tuple<T...>, index_list<indices...>>::tuple_ptr = reinterpret_cast<char const*>(&tuple);

template<typename... Ts>
std::size_t index_of(void* p, std::tuple<Ts...> const& t)
{
	using offset_info = offsets<std::tuple<Ts...>>;

	static constexpr auto& array = offset_info::array;

	auto offset_p_t = static_cast<char const*>(p) - reinterpret_cast<char const*>(&t);

	auto iter = std::lower_bound( std::begin(array), std::end(array), 0,
	                             [=] (auto lhs, auto) {return (static_cast<char const*>(lhs) - offset_info::tuple_ptr) > offset_p_t;} );

	if (iter == std::end(array))
		return -1;

	if (static_cast<char const*>(*iter) - offset_info::tuple_ptr != offset_p_t)
		return -2;

	return iter - std::begin(array);
}

int main ()
{
	std::tuple<int, double, std::string> t;
	void* p = &std::get<1>(t);

	std::cout << index_of(p, t);
}
