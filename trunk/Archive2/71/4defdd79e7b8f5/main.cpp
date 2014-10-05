#include <iostream>
#include <algorithm>
#include <tuple>

// minimalistic index-list implementation

template <std::size_t...> struct index_list {using type = index_list;};

template <typename, typename> struct concat;
template <std::size_t... i, std::size_t... j>
struct concat<index_list<i...>, index_list<j...>> : index_list<i..., j...> {};

// (Inefficient) linear recursive definition of make_indices:
template <std::size_t N> struct make_indices :
    concat<typename make_indices<N-1>::type, index_list<N-1>> {};
template <> struct make_indices<0> : index_list<> {};
template <> struct make_indices<1> : index_list<0> {};

// </>

template <typename T, typename = typename make_indices<std::tuple_size<T>::value>::type> struct offsets;

template <typename... T, std::size_t... indices>
struct offsets<std::tuple<T...>, index_list<indices...>>
{
	static std::size_t index_of(void* p, std::tuple<T...> const& t)
	{
		static const std::tuple<T...> tuple;

		static constexpr void const* array[]
		{
			&std::get<indices>(tuple)...
		};

		auto tuple_ptr = reinterpret_cast<char const*>(&tuple);

		auto offset_p_t = static_cast<char const*>(p) - reinterpret_cast<char const*>(&t);

		auto iter = std::lower_bound( std::begin(array), std::end(array), 0,
		                              [=] (auto lhs, auto) {return (static_cast<char const*>(lhs) - tuple_ptr) > offset_p_t;} );

		if (iter == std::end(array)
		 || static_cast<char const*>(*iter) - tuple_ptr != offset_p_t)
			return -1;

		return iter - std::begin(array);
	}
};


template <typename... T>
std::size_t index_of(void* p, std::tuple<T...> const& t) {return offsets<std::tuple<T...>>::index_of(p, t);}

int main ()
{
	std::tuple<int, double, std::string> t;
	void* p = &std::get<1>(t);

	std::cout << index_of(p, t);
}
