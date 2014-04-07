#include <iostream>
#include <complex>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stdexcept>

//-----------------------------------------------------------------------------

namespace mylib {

//-----------------------------------------------------------------------------

template <typename T>
T squared_distance(const std::vector<T>& a, const std::vector<T>& b)
{
    if (a.size() != b.size())
		throw std::domain_error("squared_distance requires equal length vectors");

	return std::inner_product(a.begin(), a.end(), b.begin(), T(0),
		std::plus<T>(), [](T x,T y){T z = y-x; return z*z;});
}

//-----------------------------------------------------------------------------

template <typename A, typename T>
struct allocator_subs_type;

template <template <typename...> class C, typename T, typename... S, typename R>
struct allocator_subs_type<C<T, S...>, R> { using type = C<R, S...>; };

template <typename C, typename T>
struct container_subs_type;

template <template <typename...> class C, typename T, typename A, typename... B, typename S>
struct container_subs_type<C<T, A, B...>, S>
{
	using type = C<S, typename allocator_subs_type<A, S>::type, B...>;
};

// a generic concept "Container" should be used here instead of requiring ::size_type
template <typename A, typename = typename A::size_type>
using container_value_type = typename A::value_type;

template <typename F, typename A, typename... B>
using container_result = container_subs_type<A, typename std::result_of<F(
	container_value_type <A>, container_value_type <B>...
)>::type>;

//-----------------------------------------------------------------------------

struct _or
{
	constexpr bool operator()() const { return false; }

	template <typename A, typename... B>
	constexpr bool operator()(A&& a, B&&... b) const
		{ return std::forward<A>(a) || operator()(std::forward<B>(b)...); }
};

struct _do { template <typename... A> _do(A&&...) { } };

template <typename F, typename R, typename I, typename E, typename... J>
void loop(const F& f, R r, I i, E e, J... j)
{
	for (; i != e; _do{++r, ++i, ++j...})
		*r = f(*i, *j...);
}

//-----------------------------------------------------------------------------

template <typename F>
struct apply : F
{
	using F::operator();

	template <typename A, typename... B>
	typename container_result<apply, A, B...>::type
	operator()(const A& a, const B&... b) const
	{
		using R = typename container_result<apply, A, B...>::type;

		if (_or()(a.size() != b.size()...))
			throw std::domain_error("vector operation must have equal length vectors");

		R result;
		result.reserve(a.size());
		auto r = std::back_inserter(result);
		loop(*this, r, a.begin(), a.end(), b.begin()...);
		return result;
	}
};

//-----------------------------------------------------------------------------

#define MYLIB_OP_UNARY(NAME, OP)                                \
                                                                \
namespace operators {                                           \
struct NAME                                                     \
{                                                               \
	template <typename A>                                        \
	constexpr auto                                               \
	operator()(A&& a) const                                      \
	-> decltype(OP std::forward<A>(a))                           \
		{ return OP std::forward<A>(a); }                         \
};                                                              \
}                                                               \
                                                                \
template <typename A>                                           \
typename container_result<apply<operators::NAME>, A>::type      \
operator OP(const A& a)                                         \
{                                                               \
	return apply<operators::NAME>()(a);                          \
}                                                               \

//-----------------------------------------------------------------------------

#define MYLIB_OP_BINARY(NAME, OP)                               \
                                                                \
namespace operators {                                           \
struct NAME                                                     \
{                                                               \
	template <typename A, typename B>                            \
	constexpr auto                                               \
	operator()(A&& a, B&& b) const                               \
	-> decltype(std::forward<A>(a) OP std::forward<B>(b))        \
		{ return std::forward<A>(a) OP std::forward<B>(b); }      \
};                                                              \
}                                                               \
                                                                \
template <typename A, typename B>                               \
typename container_result<apply<operators::NAME>, A, B>::type   \
operator OP(const A& a, const B& b)                             \
{                                                               \
	return apply<operators::NAME>()(a, b);                       \
}                                                               \

//-----------------------------------------------------------------------------

MYLIB_OP_UNARY(plus,  +)
MYLIB_OP_UNARY(minus, -)

MYLIB_OP_BINARY(add, +)
MYLIB_OP_BINARY(sub, -)
MYLIB_OP_BINARY(mul, *)
MYLIB_OP_BINARY(div, /)
MYLIB_OP_BINARY(mod, %)

MYLIB_OP_BINARY(eq,  ==)
MYLIB_OP_BINARY(neq, !=)
MYLIB_OP_BINARY(gt,  >)
MYLIB_OP_BINARY(lt,  <)
MYLIB_OP_BINARY(ge,  >=)
MYLIB_OP_BINARY(le,  <=)

MYLIB_OP_UNARY(_not, !)
MYLIB_OP_BINARY(_and, &&)
MYLIB_OP_BINARY(_or,  ||)

MYLIB_OP_UNARY(bit_not, ~)
MYLIB_OP_BINARY(bit_and, &)
MYLIB_OP_BINARY(bit_or,  |)
MYLIB_OP_BINARY(bit_xor, ^)

//-----------------------------------------------------------------------------

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T> &v)
{
	out << "{ ";
	for (auto p : v)
		out << p << ' ';
	return out << "}";
}

#define say(x) std::cout << "" #x " = " << (x) << std::endl

//-----------------------------------------------------------------------------

}  // namespace mylib

//-----------------------------------------------------------------------------

int main()
{
	using namespace mylib;

	std::vector<double> origin{0, 0, 0}, a{3, 4, 5}, b{-1, -2, -3};
	say(origin);
	say(a);
	say(b);
	say(-a);
	say(+b);
	say(a+b);
	say(a-b);
	say(b-a);
	std::cout << std::endl;

	std::vector<std::complex<double> > x{{0, 0}, {3, 4}}, y{{-1, -2}, {5, 6}};
	say(x);
	say(y);
	say(-x);
	say(+y);
	say(x+y);
	say(x-y);
	say(y-x);
	std::cout << std::endl;

	std::vector<std::vector<double> > u{{0, 0, 0}, {3, 4, 5}};
	std::vector<std::vector<int> >    v{{-1, -2, -3}, {5, 6, 7}};
	say(u);
	say(v);
	say(-u);
	say(+v);
	say(u+v);
	say(u-v);
	say(v-u);
	std::cout << std::endl;

	say(squared_distance(origin,a));
	say(squared_distance(origin,b));
	std::cout << std::endl;
}