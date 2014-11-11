#include <tuple>
#include <type_traits>


template <template <class T> class, typename, long = 0>
struct find_if;

template <template <class T> class Pred, typename T, long pos, typename... tail>
struct find_if<Pred, std::tuple<T, tail...>, pos> :
    std::conditional<Pred<T>::value,
	                 std::integral_constant<int64_t, pos>,
	                 find_if<Pred, std::tuple<tail...>, pos+1>>::type {};

template <template <class T> class Pred>
struct find_if<Pred, std::tuple<>> : std::integral_constant<int64_t, -1> {};

template <template <class, class> class T, class U>
struct bind
{
	template <class X>
	using first  = T<U, X>;
	template <class X>
	using second = T<X, U>;
};

struct Base {};
struct B : Base {};
struct A {};
struct C {};

using Tuple = std::tuple<A, B, C>;

static_assert(find_if<bind<std::is_base_of, Base>::first, Tuple>::value == 1, "");

int main(){}
