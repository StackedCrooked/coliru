#include <iostream>
#include <vector>
#include <set>

struct interval
{
    int _lower, _upper;
};


bool is_overlap(const std::vector<interval>& U)
{
	auto cmp = [](interval i1, interval i2) -> bool {
		return i1._upper < i2._lower;
	};
	std::set<interval, decltype(cmp)> S(cmp);
	for (auto& i : U) {
		if (S.find(i) != S.end()) return true;
		S.insert(i);
	}
    return false;
}

int main()
{
	std::vector<interval> T = {{3,5}, {1,2}, {6,8}, {4,17}};
	std::cout << is_overlap(T) << std::endl;
}
