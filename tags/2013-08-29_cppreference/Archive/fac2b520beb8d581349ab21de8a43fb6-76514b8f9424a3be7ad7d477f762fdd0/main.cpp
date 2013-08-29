#include <cmath>
#include <iostream>
#include <limits>

int main()
{
    std::string s = "2000000000";
    int x = atoi(s.c_str());
	x *= 2;
	std::cout << x;
}
