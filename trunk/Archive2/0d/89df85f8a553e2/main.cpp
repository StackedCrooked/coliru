#include <type_traits>

// lightweight type list
template <class...> struct type_list {};

template <class T> struct identity {using type = T;};

template <typename T, typename... E>
class best_conversion
{
    template <typename...> struct overloads {};

	template <typename U, typename... Rest>
	struct overloads<U, Rest...> :
		overloads<Rest...>
	{
		using overloads<Rest...>::call;

		static identity<U> call(U);
	};

	template <typename U>
	struct overloads<U>
	{
		static identity<U> call(U);
	};

	template <typename... E_>
	static identity<typename decltype(overloads<E_...>::call(std::declval<T>()))::type>
	best_conv(int);
	
	template <typename...>
	static identity<void> best_conv(...);

public:

	using type = typename decltype(best_conv<E...>(0))::type;
};

template <typename... T>
using best_conversion_t = typename best_conversion<T...>::type;

#include <string>

static_assert( std::is_same<best_conversion_t<int, int, int>, int>{}, "" );
static_assert( std::is_same<best_conversion_t<int, long, float, std::string>, void>{}, "" );
static_assert( std::is_same<best_conversion_t<int>, void>{}, "" );

int main()
{
}
