#include <type_traits>

struct A1{};
struct B1{};

template<class A, class B, class=void>
class Class { };

template<class B> class Class<A1,B> { };
template<class A> class Class<A,B1, typename std::enable_if<!std::is_same<A,A1>::value>::type> { };

int main()
{
    Class<A1, B1> c;
	(void)c;
}
