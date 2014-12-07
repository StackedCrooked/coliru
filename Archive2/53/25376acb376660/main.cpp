#include <type_traits>

// lightweight type list
template <class...> struct type_list {};

template <class T> struct identity {using type = T;};

template <typename T, typename... E>
class best_conversion
{
    template <typename...> struct overloads;

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

	template <typename, typename, typename=void>
	struct best_conv : std::false_type
	{
		// Specify behavior for ambiguity or error
		using type = void;
	};

	template <typename T_, typename... E_>
	struct best_conv <T_, type_list<E_...>,
			decltype(void(overloads<E_...>::call(std::declval<T>())))>
		: std::true_type
	{
		using type = typename decltype(overloads<E_...>::call(std::declval<T>()))::type;
	};

	using best_conv_spec = best_conv<T, type_list<E...>>;

public:

	using type = typename best_conv_spec::type;
	// Indicates success:
	static constexpr bool value = best_conv_spec::value;
};

template <typename... T>
using best_conversion_t = typename best_conversion<T...>::type;

#include <string>

static_assert( std::is_same<best_conversion_t<int, int, int>, int>{}, "" );
static_assert( std::is_same<best_conversion_t<int, long, float, std::string>, void>{}, "" );
static_assert( std::is_same<best_conversion_t<int>, void>{}, "" );

int main() {}
