#include <cstddef>
#include <iostream>
#include <tuple>
#include <utility>

template <typename T, T... Ints>
struct integer_sequence {
    typedef T value_type;
	static constexpr size_t size() { return sizeof...(Ints); }
};

template <size_t... Ints>
using index_sequence = integer_sequence<size_t, Ints...>;

namespace internal {

template <typename T, T N, T M, T... Ints>
struct make_integer_range : make_integer_range<T, N, M-1, M-1, Ints...> {};

template <typename T, T N, T... Ints>
struct make_integer_range<T, N, N, Ints...> : integer_sequence<T, Ints...> {};

} // namespace internal

template <typename T, T N>
using make_integer_sequence = internal::make_integer_range<T, 0, N>;

template <size_t N>
using make_index_sequence = make_integer_sequence<size_t, N>;

template <typename... Args>
using index_sequence_for = make_index_sequence<sizeof...(Args)>;

namespace internal {

template <typename... Args>
class unpacker {
public:
	typedef index_sequence_for<Args...> indices_type;

	explicit unpacker(std::tuple<Args...>& args)
		: args(args)
	{
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        std::cout << "sizeof...(Args)                     = " << sizeof...(Args) << std::endl;
        std::cout << "index_sequence_for<>::size()        = " << index_sequence_for<>::size() << std::endl;
        std::cout << "index_sequence_for<Args...>::size() = " << index_sequence_for<Args...>::size() << std::endl;
        std::cout << "indices_type::size()                = " << indices_type::size() << std::endl;
	}

private:
	std::tuple<Args...>& args;

	template <typename Func, size_t... I>
	void unpack_and_call(Func&& func, index_sequence<I...>)
	{
		return func(std::get<I>(args)...);
	}
};

} // namespace internal

template <typename... Args>
internal::unpacker<Args...> unpack_tuple(std::tuple<Args...>& args)
{
	return internal::unpacker<Args...>{ args };
}

int main()
{
	std::tuple<> empty{};
	auto&& unpacker = unpack_tuple(empty);
    (void)(unpacker);
}