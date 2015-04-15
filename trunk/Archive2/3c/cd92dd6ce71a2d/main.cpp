#include <iostream>
#include <utility>

template <typename T, T... v>
struct value_pack {
    static constexpr T array[] {v...};
	static constexpr std::size_t len = sizeof...(v);
	using type = value_pack;
};
template <typename T, T... v>
constexpr T value_pack<T, v...>::array[];


template <typename T, std::size_t p1, std::size_t p2,
          typename pack,
          typename=std::make_index_sequence<pack::len>>
struct SwapTs;
template <typename T, std::size_t p1, std::size_t p2,
          typename pack, std::size_t...indices>
struct SwapTs<T, p1, p2, pack, std::index_sequence<indices...>> :
	value_pack<T,  pack::array[(indices==p1 || indices==p2)*(p1^p2) ^ indices)]...> {};

int main()
{
	using t = SwapTs<int, 1, 2, value_pack<int, 0, 1, 2, 3>>::type;
	for (auto i : t::array)
		std::cout << i << ", ";
}
