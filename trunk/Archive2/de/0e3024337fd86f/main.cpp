#include <array>
#include <iostream>
#include <vector>

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

template<typename ... Args>
auto Make(int const * iter)
{
	constexpr std::size_t size = sizeof...(Args);
	return std::array<int, size>{{Args::Get(*iter++) ...}};
//	return std::array<int, size>{{Args::Get(iter[?]) ...}};
}

int main()
{
	std::vector<int> v{0, 1, 2, 3, 4};
	auto array = Make<Identity, Double, Identity, Double>(v.data());
	for (auto  i : array) std::cout << i << "\n";
}