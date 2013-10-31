#include <iostream>
#include <algorithm>
#include <iterator>

struct g
{
    g():n(0){}
	int operator()() { return n++; }
	int n;
};

int main()
{
	int a[10];
	std::generate(a, a+10, g());
	std::copy(a, a+10, std::ostream_iterator<int>(std::cout, " "));
}