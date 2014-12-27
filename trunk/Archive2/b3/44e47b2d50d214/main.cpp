#include <iostream>
#include <algorithm>
#include <vector>

int main()
{
    std::vector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8, };

	std::remove(vec.begin(), vec.end(), 1);

	for (auto element : vec)
		std::cout << element;

	std::cin.ignore();
	return 0;
}