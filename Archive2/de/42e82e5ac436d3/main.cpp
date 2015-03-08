#include <iostream>
#include <boost/container/flat_set.hpp>
#include <algorithm>
#include <iterator>

int main()
{
    boost::container::flat_set<int> s { 1, 2, 3 };
	s.erase(std::remove_if(std::begin(s), std::end(s), [](int v) { return v == 2;}), std::end(s));
	std::copy(std::begin(s), std::end(s), std::ostream_iterator<int>(std::cout, " "));
	return 0;
}