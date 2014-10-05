#include <iostream>
#include <iomanip>
#include <typeinfo>
#include <tuple>
#include <cxxabi.h>

template<typename... T>
struct Specific
{
    void DoSomething()
	{
		int status;
		std::initializer_list<bool> { std::cout << abi::__cxa_demangle(typeid(T).name(), 0, 0, &status) << ' '... };
		//std::initializer_list<bool> { std::cout << typeid(T).name() << ' '... };
		std::cout << '\n';
	}
};

template<typename... T>
Specific<T...> create_specific()
{ return {}; }

template <std::size_t...> struct index_list {using type = index_list;};

template <typename, typename> struct concat;
template <std::size_t... i, std::size_t... j> struct concat<index_list<i...>, index_list<j...>> : index_list<i..., j...> {};

template <std::size_t N>
struct make_index_list : concat<typename make_index_list<N-1>::type, index_list<N>> {};
template <>
struct make_index_list<0> : index_list<0> {};

template <unsigned base, unsigned exp>
struct ipow {static const unsigned value; };
template <unsigned base>
struct ipow<base, 0> {static const unsigned value; };

template <unsigned base, unsigned exp>
const unsigned ipow<base, exp>::value = base*ipow<base, exp-1>::value;
template <unsigned base>
const unsigned ipow<base, 0>::value = 1;

template <typename T, std::size_t len, std::size_t dim>
struct construct_array
{
	using type = typename construct_array<T, len, dim-1>::type[len];
};

template <typename T, std::size_t len>
struct construct_array<T, len, 1>
{
	using type = T[len];
};

template <std::size_t depth,
          typename A,
          typename = typename make_index_list<ipow<std::tuple_size<A>::value, depth>::value- 1>::type>
class create_lookup;

template <std::size_t depth, typename ... First, std::size_t... indices>
class create_lookup<depth, std::tuple<First...>, index_list<indices...>>
{
	template <typename... Args>
	static void work()
	{
		create_specific<Args...>().DoSomething();
	}

	static const auto length = sizeof...(First);

	template <std::size_t index, typename = typename make_index_list<depth-1>::type>
	struct get_ptr;

	template <std::size_t index, std::size_t ... type_indices>
	struct get_ptr<index, index_list<type_indices...>>
	{
		static void(* const value)();
	};

public:

	static const typename construct_array<void(*const)(), length, depth>::type arr;
};

template <std::size_t depth, typename ... First, std::size_t... indices>
template <std::size_t index, std::size_t ... type_indices>
void(*const create_lookup<depth, std::tuple<First...>, index_list<indices...>>::get_ptr<index, index_list<type_indices...>>::value)() = work< typename std::tuple_element<index / ipow<length, depth-type_indices-1>::value % length, std::tuple<First...>>::type... >;

template <std::size_t depth, typename ... F, std::size_t... I>
const typename construct_array<void(* const)(), create_lookup<depth, std::tuple<F...>, index_list<I...>>::length, depth>::type
	create_lookup<depth, std::tuple<F...>, index_list<I...>>::arr{
		get_ptr<I>::value...
	};

	struct A {};
	struct B {};
	struct C {};

int main()
{

	auto arr = create_lookup<3, std::tuple<A, B, C>>::arr;
	for (int i = 0; i < 3; ++i)
	for (int j = 0; j < 3; ++j)
	for (int k = 0; k < 3; ++k)
	{
		std::cout << i << ' ' << j << ' ' << k << ": ";
		arr[i][j][k]();
	}
}

