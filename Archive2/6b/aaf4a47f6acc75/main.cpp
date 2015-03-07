#include <iostream>
#include <algorithm>
using namespace std;

template <typename ForwardIterator>
inline
    std::pair< std::pair<ForwardIterator, ForwardIterator>, std::pair<int, int> > minmax_element_count ( ForwardIterator first, ForwardIterator last )
{
	auto minmax_elem_pair = std::minmax_element(first, last);
	auto min_elem_count = std::count(first, last, *minmax_elem_pair.first);
	auto max_elem_count = std::count(first, last, *minmax_elem_pair.second);
	//return std::make_pair (minmax_elem_pair, std::make_pair (min_elem_count, max_elem_count));
	return {minmax_elem_pair, {min_elem_count, max_elem_count}};
}

int main() 
{
	int tif_array [] = {2, 6, 6, 3, 4, 5, 1, 1, 6};

	auto minmax_count_test = ::minmax_element_count(std::begin(tif_array), std::end(tif_array));

	std::cout << "min element is: " << *minmax_count_test.first.first << " occuring " << minmax_count_test.second.first << " time(s). \n";
	std::cout << "max element is: " << *minmax_count_test.first.second << " occuring " << minmax_count_test.second.second << " time(s). \n";
	
	return 0;
}