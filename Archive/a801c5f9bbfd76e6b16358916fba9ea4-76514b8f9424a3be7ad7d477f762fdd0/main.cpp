#include <cmath>
#include <iostream>
#include <limits>

int main()
{
    int x = std::numeric_limits<int>::max();
	x += 1;
	std::cout << x;
}
