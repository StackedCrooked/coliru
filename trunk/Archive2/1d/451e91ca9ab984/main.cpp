#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <vector>
 
int main()
{
    using std::begin;
	using std::end;

	std::vector<double> squares;//{1., 4., 9., 16., 25.};
	std::vector<double> numbers;
	std::transform(begin(squares), end(squares), std::back_inserter(numbers), &std::sqrt);
	for (auto n : numbers) std::cout << n << ' ';
	endl(std::cout);
}
