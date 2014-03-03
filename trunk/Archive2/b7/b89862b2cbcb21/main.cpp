
#include <type_traits>
#include <iostream>
#include <iomanip>

struct A {
    static constexpr int const x = 42;
};

struct B {};

template<
	typename,
	typename = void
>
struct test
	: public std::false_type
{};

template<
	typename T
>
struct test<
	T,
	typename std::enable_if<
		std::is_same<
			typename std::remove_const<decltype(T::x)>::type,
			int
		>::value,
		T
	>::type
>
	: public std::true_type
{};

signed
main() {
	std::cout
		<< std::boolalpha
		<< "A: " << test<A>::value << "\n"
		<< "B: " << test<B>::value << "\n"
	;
	return 0;
}
