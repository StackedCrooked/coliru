#include <iostream>
#include <random>
#include <vector>

int main()
{
    std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<> dist(0, 19);
	std::vector<int> v(15);
	const int runs = 1000 * 1000;
	for (int i = 0; i < runs; ++i)
	{
		++v[dist(mt) % v.size()];
	}

	for (int i = 0; i < v.size(); ++i)
	{
		std::cout << i << ": " << v[i] << "\n";
	}
}