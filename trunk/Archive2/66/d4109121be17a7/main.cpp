#include <type_traits>
#include <vector>
#include <tuple>
#include <iostream>

// indices are a classic
template< std::size_t... Ns >
struct indices
{
    using next = indices< Ns..., sizeof...(Ns) >;
};

template< std::size_t N >
struct make_indices
{
	using type = typename make_indices< N - 1 >::type::next;
};

template<>
struct make_indices< 0 >
{
	using type = indices<>;
};

// we need something to find a type's index within a list of types
template<typename T, typename U, std::size_t = 0>
struct index {};

template<typename T, typename... Us, std::size_t N>
struct index<T, std::tuple<T, Us...>, N>
	: std::integral_constant<std::size_t, N>{};

template<typename T, typename U, typename... Us, std::size_t N>
struct index<T, std::tuple<U, Us...>, N>
	: index<T, std::tuple<Us...>, N + 1>{};

// we need a way to remove duplicate types from a list of types
template<typename T, typename I = void> struct unique;

// step 1: generate indices
template<typename... Ts>
struct unique< std::tuple<Ts...>, void >
	: unique< std::tuple<Ts...>, typename make_indices<sizeof...(Ts)>::type >
{
};

// step 2: remove duplicates. Note: No recursion here!
template<typename... Ts, std::size_t... Is>
struct unique< std::tuple<Ts...>, indices<Is...> >
{
	using type = decltype(std::tuple_cat(std::declval<
		typename std::conditional<index<Ts, std::tuple<Ts...>>::value == Is, std::tuple<Ts>, std::tuple<>>::type
	>()...));
};

// a helper to turn Ts... into std::vector<Ts>...
template<typename> struct vectorize;

template<typename... Ts>
struct vectorize<std::tuple<Ts...>>
{
	using type = std::tuple< std::vector<Ts>... >;
};

// now you can easily use it to define your Store
template<typename... Ts> class Store
{
	using Storage = typename vectorize<typename unique<std::tuple<Ts...>>::type>::type;
	Storage storage;

	template<typename T>
	decltype(std::get<index<T, typename unique<std::tuple<Ts...>>::type>::value>(storage))
		slot()
	{
			return std::get<index<T, typename unique<std::tuple<Ts...>>::type>::value>(storage);
	}

	

public:
	template<typename T> void add(T mValue) {
		slot<T>().push_back(mValue);
	}

	template<typename T> std::vector<T>& get() {
		return slot<T>();
	}
	
};
class Store_Helper
{
public:
	template< class... Args>
	Store<Args...> operator()(const Args&...  args)
	{
		auto helper = [](auto... param) {
			Store<decltype(param)...> stream;
			using List = int[];
			(void)List{ 0, ((void)(stream.add(param)), 0) ... };
			return stream;
		};
		return helper(args...);
	}
};
int main()
{
	Store_Helper store_helper;
	auto store = store_helper(1, 2, std::string("test1"), std::string("test2"), 3.5, 2.5);
    
   std::cout<< store.get<int>()[0] <<'\n';//integer aval
   std::cout<< store.get<int>()[1] <<'\n';//integer dovom
   std::cout<< store.get<std::string>()[1] <<'\n';//string dovom
   std::cout<< store.get<double>()[1];//double dovom
}