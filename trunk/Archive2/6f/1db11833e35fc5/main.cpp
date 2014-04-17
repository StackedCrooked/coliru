#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <numeric>
#include <vector>
#include <boost/timer/timer.hpp>

int main()
{
    using ui64 = std::uint_fast64_t;

	const std::size_t size = 100000000;
	const ui64 initial_value = 123;
	const std::size_t replications = 10;

	ui64 sum_a = 0;
	{
		std::puts("C-style array: alloc, write, read, dealloc.");
		boost::timer::auto_cpu_timer timer;
		for (std::size_t replication = 0; replication != replications; ++replication)
		{
			ui64 * a = new ui64[size];
			std::iota(a, a + size, initial_value);
			sum_a = std::accumulate(a, a + size, ui64(0));
			delete[] a;
		}
	}

	ui64 sum_v = 0;
	{
		std::puts("C++ std::vector: alloc, write, read, dealloc.");
		boost::timer::auto_cpu_timer timer;
		for (std::size_t replication = 0; replication != replications; ++replication)
		{
			std::vector<ui64> v(size);
			std::iota(begin(v), end(v), initial_value);
			sum_v = std::accumulate(begin(v), end(v), ui64(0));
		}
	}

	bool equal = (sum_a == sum_v);
	int result = equal ? 0 : 1;

	return result;
}
