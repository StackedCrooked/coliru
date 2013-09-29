#include <vector>
#include <iostream>

int main()
{
    std::vector<int> someInts;

	for (int x = 0; x < 5; ++x)
		for (int y = 0; y < 5; ++y)
			if (true)
				someInts.push_back(x*y);

	std::cout << someInts.size();

	std::cin.get();
}