
#include <iostream>
#include <tuple>

namespace std
{
    template <std::size_t... ARGS>
	struct _integer_sequence { static void print() { int __attribute__((unused)) arr[] = { (void(std::cout << ARGS), 0)... }; } constexpr static int s_size() { return sizeof...(ARGS); } constexpr int m_size() {return s_size();} };
	template <std::size_t N, std::size_t... ARGS>
	struct _make_integer_sequence : _make_integer_sequence<N - 1, N - 1, ARGS...> {};
	template <std::size_t... ARGS>
	struct _make_integer_sequence<0, ARGS...> : _integer_sequence<ARGS...> {};
}

template <typename T, std::size_t... ARGS>
void print_tuple(T& t, std::_integer_sequence<ARGS...>)
{
    int __attribute__((unused)) arr[] = {(void(std::cout << std::get<ARGS>(t)), 0)...};
}

template <typename Cr, typename Tr, typename... ARGS>
std::basic_ostream<Cr, Tr>& operator<<(std::basic_ostream<Cr, Tr>& os, std::tuple<ARGS...>& t)
{
    os << "(";
    print_tuple(t, std::_make_integer_sequence<sizeof...(ARGS)>());
    os << ")";
    return os;
}

template <typename T, std::size_t... ARGS>
void func(std::_integer_sequence<ARGS...>&& is, T&& t)
{
    std::cout << std::_integer_sequence<ARGS...>::s_size() << std::endl; // prints N by the static function
    std::cout << is.m_size() << std::endl; // prints N by the member method
    std::remove_reference<decltype(is)>::type::print(); // prints: 01234..N
    std::cout << std::endl;
    std::cout << t << std::endl; // prints a tuple
}

int main()
{
	func(std::_make_integer_sequence<5>(), std::make_tuple(1, 3, 5, 7, 9));
}
