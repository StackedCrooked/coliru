#include <type_traits>

template <class T> using eval = typename T::type;

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
	static identity<eval<decltype(overloads<E_...>::call(std::declval<T>()))>>
	best_conv(int);

	template <typename...>
	static identity<void> best_conv(...);

public:

	using type = eval<decltype(best_conv<E...>(0))>;
};

template <typename... T>
using best_conversion_t = eval<best_conversion<T...>>;

#include <string>

static_assert( std::is_same< best_conversion_t<int, long, short>,       void >{}, "" );
static_assert( std::is_same< best_conversion_t<int, long, std::string>, long >{}, "" );
static_assert( std::is_same< best_conversion_t<int>,                    void >{}, "" );

int main() {}
