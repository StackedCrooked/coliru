#include <cstddef>
#include <climits>
#include <array>

template <std::size_t n>
struct integral_type {
	typedef std::array < uint64_t, ( n / sizeof( uint64_t ) ) + ( ( n % sizeof( uint64_t ) ) > 0 ) > type;
};

template <>
struct integral_type<0> {
	typedef uint8_t type;
};

template <>
struct integral_type<1> {
	typedef uint8_t type;
};

template <>
struct integral_type<2> {
	typedef uint16_t type;
};

template <>
struct integral_type<3> {
	typedef uint32_t type;
};

template <>
struct integral_type<4> {
	typedef uint32_t type;
};

template <>
struct integral_type<5> {
	typedef uint64_t type;
};

template <>
struct integral_type<6> {
	typedef uint64_t type;
};

template <>
struct integral_type<7> {
	typedef uint64_t type;
};

template <>
struct integral_type<8> {
	typedef uint64_t type;
};

namespace detail {
	template <std::size_t n, std::size_t m>
	struct t_pow {
		static const std::size_t value = n * t_pow<n, m - 1>::value;
	};

	template <std::size_t n>
	struct t_pow<n, 0> {
		static const std::size_t value = 1;
	};
}

template <std::size_t n, std::size_t m, typename T = typename integral_type<( n + m ) / 8>::type>
struct q {
	static_assert( (n + m) <= (sizeof( T ) * CHAR_BIT), "type for T is not large enough to back this q<>" );
	T res;

	q( ) = default;

	template <typename F, typename = typename std::enable_if<std::is_floating_point<F>::value>::type>
	q( F f ) : res( static_cast<T>( f * detail::t_pow<2, m>::value ) ) {

	}

	template <typename I, typename = typename std::enable_if<std::is_integral<I>::value && (std::is_signed<I>::value == std::is_signed<T>::value)>::type>
	q( I u ) : res( static_cast<T>( u << m ) ) {
		
	}
};

int main()
{
    q<26, 6> arf = 20;
}
