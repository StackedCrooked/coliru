#include <iostream>
#include <algorithm>
#include <vector>
#include <random>

int main()
{
    int times = 10;
	while(times--) {
		std::vector<int> base { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		std::vector<int> temp { base };
		std::random_device rd;
		std::mt19937 g(rd());
		std::shuffle(std::begin(temp), std::end(temp), g);

		for(auto e : temp)
			std::cout << e << " ";

		std::cout << std::endl;
	}

	return 0;
}
