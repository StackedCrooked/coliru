#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <future>
#include <numeric>
using namespace std;

template<class InputIterator>
int parallel_sum(InputIterator beg, InputIterator end)
{
   typename InputIterator::difference_type len = end - beg;
    if ( len < 1000 )
		return std::accumulate(beg, end, 0);

	InputIterator mid = beg + len / 2;
	auto handle = std::async( std::launch::async, [&]
	{
		int partial_sum = parallel_sum( mid, end );
		cout << "partial_sum=" << partial_sum << endl;
		return partial_sum;
	} );
	int sum = parallel_sum(beg, mid);
	return sum + handle.get();
}

int main()
{
    std::vector<int> v(10000, 1);
	std::cout << "The sum is " << parallel_sum( v.begin(), v.end() ) << '\n';

	return 0;
}