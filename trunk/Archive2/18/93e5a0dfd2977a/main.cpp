#include <vector>
#include <array>
#include <string>
#include <algorithm>
#include <numeric>
#include <iostream>

template <typename E>
size_t bin(const E& elem, size_t digit)
{
	return elem.size() > digit ? size_t(elem[digit]) + 1 : 0;
}

template <size_t R, typename C, typename P>
void radix_sort(P& pos, const C& data, size_t digit)
{
    using A = std::array<size_t, R + 1>;
	A count = {};
	P prev(pos);

	for (auto i : prev)
		++count[bin(data[i], digit)];

	A done = {}, offset = {{0}};
	std::partial_sum(count.begin(), count.end() - 1, offset.begin() + 1);

	for (auto i : prev)
	{
		size_t b = bin(data[i], digit);
		pos[offset[b] + done[b]++] = i;
	}
}

struct shorter
{
	template <typename A>
	bool operator()(const A& a, const A& b) { return a.size() < b.size(); }
};

template <size_t R, typename C>
std::vector<size_t> radix_sort(const C& data)
{
	std::vector<size_t> pos(data.size());
	std::iota(pos.begin(), pos.end(), 0);

	size_t width = std::max_element(data.begin(), data.end(), shorter())->size();

	for (long digit = long(width) - 1; digit >= 0; --digit)
		radix_sort<R>(pos, data, size_t(digit));

	return pos;
}

std::vector<std::string> generate()
{
	std::vector<std::string> data =
	{
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

	return data;
}

int main()
{
	std::vector<std::string> data = generate();
	std::vector<size_t> pos = radix_sort<128>(data);
	for (auto i : pos)
		std::cout << data[i] << std::endl;
}