#include <iostream>
#include <vector>
#include <map>
#include <functional>

int main()
{
    std::vector<int> a1 = {1,1,2,3,3,4,5,5,6},
	                 a2 = {1,2,3,4,5,6};

	std::map<std::reference_wrapper<const decltype(a1)::value_type>, int> occurences;
	for (auto&& i : a1)
		++occurences[std::cref(i)];
	for (auto&& i : a2)
		--occurences[std::cref(i)];

	std::vector<int> vec;
	for (auto p : occurences)
		vec.insert( vec.end(), std::max(0, p.second), p.first );

	for (auto i : vec)
		std::cout << i << ", ";
}
