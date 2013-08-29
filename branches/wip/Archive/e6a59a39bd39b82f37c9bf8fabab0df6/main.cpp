#include <iostream>
#include <numeric>
#include <vector>

template <typename C>
void println(C const & c)
{
   for (auto && v : c) std::cout << v << ' ';
    std::cout << '\n';
}

int main()
{
	std::vector<int> c(10);
	iota(begin(c), end(c), 0);
	println(c);
	std::vector<int> const d{c};
	println(d);
}
