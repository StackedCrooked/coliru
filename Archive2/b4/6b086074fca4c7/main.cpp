#include <iostream>
#include <array>
#include <utility>
#include <tuple>

template <size_t I, typename Functor, typename = std::make_index_sequence<I>> struct Apply;

template <size_t I, typename Functor, std::size_t... Indices>
struct Apply<I, Functor, std::index_sequence<Indices...>> :
    private std::tuple<Functor>
{
    Apply(Functor f) :  std::tuple<Functor>(f) {}
    Apply() = default;
    
    template <typename InputRange1, typename InputRange2, typename OutputRange>
	void operator()(OutputRange& dst, const InputRange1& lhs, const InputRange2& rhs) const
	{
		(void)std::initializer_list<int>
		{ (dst[Indices] = std::get<0>(*this)(lhs[Indices], rhs[Indices]), 0)... };
	}
};

int main()
{
	std::array<int, 4> iv4 { 1,2,3,4 };
	std::array<double, 4> id4 { .1, .2, .3, .4 };
	std::array<double, 4> dest;

	Apply<4, std::plus<>>()(dest, iv4, id4);

	for (auto d : dest)
		std::cout << d << ", ";
}
