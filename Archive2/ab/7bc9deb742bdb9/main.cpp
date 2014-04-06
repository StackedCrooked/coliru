#include <string>
#include <type_traits>

struct can_call_test
{
    template<typename F, typename... A>
	static decltype(std::declval<F>()(std::declval<A>()...), std::true_type())
	f(int);

	template<typename F, typename... A>
	static std::false_type
	f(...);
};

template<typename F, typename... A>
using can_call = decltype(can_call_test::f<F, A...>(0));

template<typename T, typename F>
constexpr bool is_callable_with(F&&) { return can_call<F, T>{}; }

void f1(int) { }
void f2(const std::string&) { }

int main ()
{
	static_assert( is_callable_with<int>(f1), "Oops");
	static_assert(!is_callable_with<int>(f2), "Oops");
}
