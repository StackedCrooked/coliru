#include <array>
#include <cstdint>
#include <cstddef>

    typedef char sbyte;
    typedef unsigned char byte;
	typedef unsigned char uchar;
	typedef unsigned short ushort;
	typedef unsigned int uint;
	typedef unsigned long ulong;
	typedef long long llong;
	typedef unsigned long long ullong;

    typedef int8_t int8;
	typedef uint8_t uint8;
	typedef int16_t int16;
	typedef uint16_t uint16;
	typedef int32_t int32;
	typedef uint32_t uint32;
	typedef int64_t int64;
	typedef uint64_t uint64;
	typedef float single;
    
    typedef std::size_t ulword;

    template <ulword n>
	struct integral_type {
		typedef std::array < uint64, ( n / sizeof( uint64 ) ) + ( ( n % sizeof( uint64 ) ) > 0 ) > type;
	};

	template <>
	struct integral_type<0> {
		typedef byte type;
	};

	template <>
	struct integral_type<1> {
		typedef byte type;
	};

	template <>
	struct integral_type<2> {
		typedef uint16 type;
	};

	template <>
	struct integral_type<3> {
		typedef uint32 type;
	};

	template <>
	struct integral_type<4> {
		typedef uint32 type;
	};

	template <>
	struct integral_type<5> {
		typedef uint64 type;
	};

	template <>
	struct integral_type<6> {
		typedef uint64 type;
	};

	template <>
	struct integral_type<7> {
		typedef uint64 type;
	};

	template <>
	struct integral_type<8> {
		typedef uint64 type;
	};

	template <ulword n>
	using integral_type_t = typename integral_type<n>::type;

	template <typename T>
	struct integral_type_of {
		typedef typename integral_type<sizeof( T )>::type type;
	};

	template <typename T>
	using integral_type_of_t = typename integral_type_of<T>::type;

    template <std::size_t n, std::size_t m, typename Signedness = int>
	struct q {
		typedef typename integral_type<4>::type core_t;


    };


int main () {
    q<26, 6> meow;
}