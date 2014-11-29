#include <type_traits>

template <typename T, typename=void> struct LessThanComparable_ : std::false_type {};

template <typename T>
struct LessThanComparable_<T, decltype(void(std::declval<T>() < std::declval<T>()))>
    : std::true_type {};

template <typename T>
using LessThanComparable = LessThanComparable_<T>;

#include <string>

int main()
{
	static_assert( LessThanComparable<std::string>::value, "" );
	static_assert( LessThanComparable<int>::value, "" );
	static_assert( !LessThanComparable<std::ostream>::value, "" );
}
