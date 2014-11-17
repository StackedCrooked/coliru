#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

template <typename T>
class ArithmeticProgression
{
    T val;
	T inc;

public:

	ArithmeticProg(T val, T inc) : val(val), inc(inc) {}

	ArithmeticProg& operator++() noexcept(noexcept(val += inc))
	{
		val += inc;
		return *this;
	}

	T operator()() noexcept(noexcept(val += inc))
	{
		auto tmp = val;
		val += inc;
		return tmp;
	}

	operator T() const noexcept {return val;}
};

template <typename T, typename U>
ArProg<typename std::common_type<T, U>::type>
makeArithmeticProg( T val, U inc )
{
	return {val, inc};
}

int main()
{
	std::vector<float> vec;
	std::generate_n( std::back_inserter(vec), 5, makeArithmeticProg(2.0f, 0.5f) );

	for (auto f : vec)
		std::cout << f << ", ";

	std::cout << '\n';

	std::iota( std::begin(vec), std::end(vec), makeArithmeticProg(2.5f, 0.3f) );

	for (auto f : vec)
		std::cout << f << ", ";
}
