
#include <type_traits>
#include <iostream>
#include <iomanip>

template<
    typename T,
	typename = bool
>
struct test
    : std::false_type
{};

template<
	typename T
>
struct test<T, decltype((void)T::x, false)>
    : public std::conditional<
        std::is_same<
            int,
            typename std::remove_const<
                typename std::remove_reference<
                	decltype(T::x)
                >::type
            >::type
        >::value,
        std::true_type,
        std::false_type
    >::type
{};

struct X1 {
    static constexpr int const x = 42;
};

struct X2 {
    static constexpr long const x = 42;
};

struct X3 {};

signed
main() {
    std::cout
		<< std::boolalpha
		<< "X1: " << test<X1>::value << "\n"
		<< "X2: " << test<X2>::value << "\n"
		<< "X3: " << test<X3>::value << "\n"
	;
	return 0;
}
