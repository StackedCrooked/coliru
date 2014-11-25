
#include <iostream>

namespace std
{
    template <std::size_t... ARGS>
	struct integer_sequence { static void print() { int arr[] = { (void(std::cout << ARGS), 0)... }; } constexpr static int s_size() { return sizeof...(ARGS); } constexpr int m_size() {return s_size();} };
	template <std::size_t N, std::size_t... ARGS>
	struct make_integer_sequence : make_integer_sequence<N - 1, N - 1, ARGS...> {};
	template <std::size_t... ARGS>
	struct make_integer_sequence<0, ARGS...> : integer_sequence<ARGS...> {};
}

template <std::size_t... ARGS>
void func(std::integer_sequence<ARGS...>&& is)
{
    std::cout << std::integer_sequence<ARGS...>::s_size() << std::endl;
    std::cout << is.m_size() << std::endl;
    std::remove_reference<decltype(is)>::type::print();
}

int main()
{
	func(std::make_integer_sequence<5>());
}
