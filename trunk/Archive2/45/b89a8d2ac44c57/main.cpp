#include <tuple>
#include <type_traits>

template <typename...> struct type_list {using type = type_list;};

template<typename...>
struct cat_type_list;

template<typename T>
struct cat_type_list<T> : T {};

template<typename... T, typename... U, typename... R>
struct cat_type_list<type_list<T...>, type_list<U...>, R...> :
    cat_type_list<type_list<T..., U...>, R...> {};


template <typename... AllBranches>
struct Unfold
{
	using type = typename cat_type_list<
		typename Unfold<AllBranches>::type...>::type;
};

template <typename T>
struct Unfold<T>
{
	using type = type_list<>;
};

template <template <typename...> class Branch, typename... Children>
struct Unfold<Branch<Children...>>
{
	using type = typename cat_type_list<
		type_list<Branch<Children...>>,
		typename Unfold<Children...>::type>::type;
};

template <typename... Children>
struct Branch
{
	using IsBranch = std::true_type;
};

struct Leaf
{
	using IsBranch = std::false_type;
};

// Add wrap Leaf in Branch N number of times:
template <int N, typename T = Leaf>
struct Nest
{
    using type = typename Nest<N-1, Branch<T>>::type;
};

template <typename T>
struct Nest<0, T>
{
	using type = T;
};


#include <typeinfo>
#include <iostream>
#include <cxxabi.h>

int main()
{
	using Expression = typename Nest<50>::type;
	typename Unfold<Expression>::type x; (void)&x; // disable this line for "generate expression only"
	int status;
	std::cout << abi::__cxa_demangle(typeid(x).name(), 0, 0, &status) << '\n';
}
