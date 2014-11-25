
#include <iostream>
template <typename... ARGS>
void empty_func(ARGS...) {}

namespace std
{
    template <std::size_t... ARGS>
	struct integer_sequence { constexpr static int size() { return sizeof...(ARGS); } };
	template <std::size_t N, std::size_t... ARGS>
	struct make_integer_sequence : make_integer_sequence<N - 1, N - 1, ARGS...> {};
	template <std::size_t... ARGS>
	struct make_integer_sequence<0, ARGS...> : integer_sequence<ARGS...> {};
}

template <std::size_t... ARGS>
void func(std::integer_sequence<ARGS...>)
{
    std::cout << std::integer_sequence<ARGS...>::size() << std::endl;
}

int main()
{
	func(std::make_integer_sequence<5>());
}
