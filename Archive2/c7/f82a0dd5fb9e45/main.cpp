#include <array>
#include <iostream>
#include <vector>
#include <utility>

struct Identity
{
    static int Get(int i)
	{
		return i;
	}
};

struct Double
{
	static int Get(int i)
	{
		return i * 2;
	}
};

template<std::size_t size, typename ... Args, std::size_t ... indexes>
auto MakeHelper(int const * iter, std::index_sequence<indexes ...>)
{
    return std::array<int, size>{{Args::Get(iter[indexes]) ...}};
}

template<typename ... Args>
auto Make(int const * iter)
{

	constexpr std::size_t size = sizeof ...(Args);
	return MakeHelper<size, Args ...>(iter, std::make_index_sequence<size>());
}

int main()
{
	std::vector<int> v{0, 1, 2, 3, 4};
	auto array = Make<Identity, Double, Identity, Double>(v.data());
	for (auto  i : array) std::cout << i << "\n";
}