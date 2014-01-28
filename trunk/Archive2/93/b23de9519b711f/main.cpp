#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/algorithm_ext.hpp>
#include <boost/range/numeric.hpp>
#include <iostream>
#include <iterator>
#include <vector>
#include <random>
#include <boost/range/istream_range.hpp>
#include <boost/range/irange.hpp>

int main()
{
    std::vector<int> vec(10);

	std::cout << "iota:" << '\n';
	boost::iota(vec, 1);
	for (auto e : vec) std::cout << e << " ";
	std::cout << '\n';

	std::cout << "reversed:" << '\n';
	for (auto e : vec | boost::adaptors::reversed) std::cout << e << " ";
	std::cout << '\n';

	std::cout << "sums:" << '\n';
	std::vector<int> sums(10);
	boost::partial_sum(vec, begin(sums));
	for (auto e : sums) std::cout << e << " ";
	std::cout << '\n';

	// perhaps as exercise?
	std::cout << "evens:" << '\n';
	std::vector<int> evens(10);
	boost::fill(evens, 2); // std::vector<int> evens(10, 2);
	boost::partial_sum(evens, begin(evens));
	for (auto e : evens) std::cout << e << " ";
	std::cout << '\n';

	boost::partial_sum(evens | boost::adaptors::reversed, begin(evens));
	for (auto e : evens) std::cout << e << " ";
	std::cout << '\n';

	// perhaps as exercise?
	std::cout << "factorials:" << '\n';
	std::vector<int> factorials(10);
	boost::partial_sum(vec, begin(factorials), std::multiplies<int>());
	for (auto e : factorials) std::cout << e << " ";
	std::cout << '\n';

	std::cout << "die:" << '\n';
	std::random_device random_device;
	std::default_random_engine random_engine(random_device());
	int a = 1, b = 6;
	std::uniform_int_distribution<int> uniform_distribution(a, b);
	auto die = std::bind(uniform_distribution, random_engine);
	std::cout << die() << '\n';

	std::cout << "die throws:" << '\n';
	std::vector<int> die_throws(10);
	boost::generate(die_throws, die); // readability: "generate die_throws using die [duh]"
	for (auto e : die_throws) std::cout << e << " ";
	std::cout << '\n';

	std::cout << "die throws, from #2 to #5:" << '\n';
	for (auto e : die_throws | boost::adaptors::sliced(2, 5)) std::cout << e << " ";
	std::cout << '\n';

	auto count_unique_low = boost::count_if( die_throws | boost::adaptors::uniqued, [](int result) { return result <= 3; } );
	auto count_unique_high = boost::count_if( die_throws | boost::adaptors::uniqued, [](int result) { return result > 3; } );
	std::cout << "count_unique_low = " << count_unique_low << '\n';
	std::cout << "count_unique_high = " << count_unique_high << '\n';

	/*
	std::vector<int> v;
	boost::push_front(v, boost::istream_range<int>(std::cin));
	for (auto e : v) std::cout << e << " ";
	std::cout << '\n';
	*/
	std::vector<int> v;
	boost::push_back(v, boost::irange(100, 200, 3)); // first, last, step-size
	for (auto e : v) std::cout << e << " ";
	std::cout << '\n';

}

