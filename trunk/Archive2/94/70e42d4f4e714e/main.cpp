#include <utility>

template <typename R, typename... Args>
struct noexcept_wrapper
{
    R (*fun)(Args...) noexcept;

	noexcept_wrapper(R (*fun)(Args...) noexcept): fun(fun) {}

	template <typename... InnerArgs>
	R operator()(InnerArgs&&... args) noexcept {
		return fun(std::forward<InnerArgs>(args)...);
	}
};

template <typename R, typename... Args>
noexcept_wrapper<R, Args...> make_noexcept_wrapper( R(*fun)(Args...) noexcept )
{
	return {fun};
}

#include <iostream>
void foo(int i) noexcept {std::cout << i << '\n';}

int main()
{
	auto wrapper = make_noexcept_wrapper(foo);
	wrapper(4);
}
