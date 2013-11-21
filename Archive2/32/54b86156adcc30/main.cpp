#include <iostream>

#include <boost/preprocessor/stringize.hpp>

template <typename T, typename U>
struct check
{
    enum { value = std::is_same
    	<typename std::remove_reference<T>::type, U>::value };
};

struct A {};

#define CHECK(T, U)								\
    std::cout << "check<"							\
	BOOST_PP_STRINGIZE(T) ", " BOOST_PP_STRINGIZE(U)			\
	">::value = [" << check<T, U>::value << ']' << std::endl;		\
    /**/

int main()
{
    CHECK(A&, A);
    CHECK(const A&, const A);
    CHECK(volatile A&, volatile A);
    CHECK(volatile const A&, volatile const A);

    CHECK(A*&, A*);
    CHECK(const A*&, const A*);
    CHECK(volatile A*&, volatile A*);
    CHECK(volatile const A*&, volatile const A*);

    return EXIT_SUCCESS;
}
