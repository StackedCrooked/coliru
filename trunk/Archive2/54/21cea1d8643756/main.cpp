#include <type_traits>
#include <vector>
#include <array>
#include <string>
#include <algorithm>
#include <numeric>
#include <iostream>

template<bool B>
using expr = std::integral_constant<bool, B>;

//-----------------------------------------------------------------------------

template <typename View, bool Var, bool Flip, size_t Radix>
class radix_sort
{
	template <typename I, typename S>
	void sort(I& idx, const S& slice) const
	{
		constexpr size_t N = Radix + 1;
		using A = std::array<size_t, (Var ? N + 1 : N)>;

		A count = {};
		I prev(idx);

		for (auto i : prev)
			++count[slice(i)];

		A alloc = {}, offset = {{0}};
		std::partial_sum(count.begin(), count.end() - 1, offset.begin() + 1);

		for (auto i : prev)
		{
			auto bin = slice(i);
			idx[offset[bin] + alloc[bin]++] = i;
		}
	}

public:
	template <typename D>
	std::vector<size_t> operator()(const D& data) const
	{
		std::vector<size_t> idx(data.size());
		std::iota(idx.begin(), idx.end(), 0);

		if (data.size() < 2)
			return idx;

		View view;
		using R = decltype(data[0]);

		size_t width = Var ?
			view.size(*std::max_element(data.begin(), data.end(),
				[view](R a, R b) { return view.size(a) < view.size(b); }
			)) :
			view.size(data[0]);

		for (size_t d = 0; d < width; ++d)
		{
			size_t digit = Flip ? width - d - 1 : d;
			sort(idx, [&view, &data, digit] (size_t i) {
				return size_t(view.at(expr<Var>(), data[i], digit));
			});
		}

		return idx;
	}
};

//-----------------------------------------------------------------------------

struct int_view
{
	template<typename A>
	size_t size(const A& a) const { return sizeof(a); }

	template <bool B, typename E>
	unsigned char at(expr<B>, const E& elem, size_t pos) const
	{
		return (elem >> pos) & 0xFF;
	}
};

//-----------------------------------------------------------------------------

struct array_view
{
	template<typename A>
	size_t size(const A& a) const { return a.size(); }

	template <typename E>
	typename E::value_type
	at(std::false_type, const E& elem, size_t pos) const
	{
		return elem[pos];
	}

	template <typename E>
	typename E::value_type
	at(std::true_type, const E& elem, size_t pos) const
	{
		using T = typename E::value_type;
		return pos < elem.size() ? elem[pos] + T(1) : T(0);
	}
};

//-----------------------------------------------------------------------------

std::array<unsigned, 100>
numbers()
{
	return {{
		162, 794, 311, 528, 165, 601, 262, 654, 689, 748,
		450,  83, 228, 913, 152, 825, 538, 996,  78, 442,
		106, 961,   4, 774, 817, 868,  84, 399, 259, 800,
		431, 910, 181, 263, 145, 136, 869, 579, 549, 144,
		853, 622, 350, 513, 401,  75, 239, 123, 183, 239,
		417,  49, 902, 944, 490, 489, 337, 900, 369, 111,
		780, 389, 241, 403,  96, 131, 942, 956, 575,  59,
		234, 353, 821,  15,  43, 168, 649, 731, 647, 450,
		547, 296, 744, 188, 686, 183, 368, 625, 780,  81,
		929, 775, 486, 435, 446, 306, 508, 510, 817, 794
	}};
}

std::vector<std::string>
strings()
{
	return {
		"subdivides",
		"main street",
		"pants",
		"impaled decolonizing",
		"argillaceous",
		"axial satisfactoriness",
		"temperamental",
		"hypersensitiveness",
		"bears",
		"hairbreadths",
		"creams surges",
		"unlaboured",
		"hoosier",
		"buggiest",
		"mauritanians",
		"emanators",
		"acclaiming",
		"zouaves dishpan",
		"traipse",
		"solarisms",
		"remunerativeness",
		"solubilizing",
		"chiseled",
		"jugular",
		"ooziness",
		"toastier",
		"baud",
		"suffixed",
		"powerless tiding",
		"disassimilated",
		"gasps",
		"flirtier",
		"uh"
	};
}

//-----------------------------------------------------------------------------

template<typename G, typename S>
void test(G generate, S sort)
{
	auto data = generate();
	auto idx = sort(data);

	std::cout << "sorted data:" << std::endl;
	for (auto i : idx)
		std::cout << data[i] << std::endl;
	std::cout << std::endl;
}

int main()
{
	test(numbers, radix_sort<int_view,   false, false, 255>());
	test(strings, radix_sort<array_view, true,  true,  127>());
}
