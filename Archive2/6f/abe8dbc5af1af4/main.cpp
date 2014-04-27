#include <vector>
#include <algorithm>
#include <assert.h>
#include <iterator>
#include <iostream>
#include <numeric>

static const int N = 10;

void foo(const bool use_runtime_input, const unsigned int runtime_input = 0)
{
    assert(runtime_input < N);
    
    std::vector<unsigned int> indexes(N);

    std::iota(indexes.begin(), indexes.begin()+N, 0);

	if (use_runtime_input) 
		std::rotate(indexes.rend() - runtime_input - 1, indexes.rend() - runtime_input, indexes.rend());

    
	std::copy(indexes.begin(), indexes.end(), std::ostream_iterator<unsigned>(std::cout, " "));
	std::cout << "\n";
}

int main()
{
    foo(false);
    foo(true);
    foo(true, 4);
    foo(true, 9);
}
