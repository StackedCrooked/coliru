#include <iostream>
#include <numeric>
#include <vector>

template <typename C>
void increment_and_println(C && c)
{
    for (auto && v : c) { ++v; std::cout << v << ' '; }
    std::cout << '\n';
}

int main()
{
	std::vector<int> c(5);
	iota(begin(c), end(c), 0);
	increment_and_println(c);
	std::vector<int> d{c};
	increment_and_println(d);
    increment_and_println(std::vector<int>{0, 1, 2, 3, 4});
}
