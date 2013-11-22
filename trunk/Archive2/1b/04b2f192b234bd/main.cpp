#include <iostream>

namespace internal {

template <typename T>
T get(int index)
{
    std::cout << __PRETTY_FUNCTION__ << " >> value from stack #" << index << std::endl;
	return T{ /* value from Lua stack */ };
}

template <int... I>
struct Indices {
	template <int J> struct Append  { typedef Indices<I..., J> type; };
};

// zero arguments
template <typename... Args>
struct StackIndices {
	typedef Indices<> type;
};

// one or more arguments
template <typename T, typename... Args>
struct StackIndices<T, Args...> {
	typedef typename StackIndices<Args...>::type::
		template Append<sizeof...(Args) + 1>::type type;
};

template <typename R, typename... Args, int... I>
R call(R (*func)(Args...), Indices<I...>)
{
	return func( get<Args>(I)... );
}

} // namespace internal

template <typename R, typename... Args>
R call(R (*func)(Args...))
{
	typedef typename internal::StackIndices<Args...>::type indices_type;
	return internal::call( func, indices_type{} );
}

void foobar(int, float, const char*)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
}

int main()
{
	call(foobar);
}