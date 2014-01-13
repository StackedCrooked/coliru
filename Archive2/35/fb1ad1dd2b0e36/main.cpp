#include <iostream>
#include <type_traits>
#include <map>

template<int C>
struct Test
{
    auto blah() const
	-> typename std::enable_if
	<
		C == 1,
		bool
	>::type
	{
		return false;
	}
};

int main()
{
	std::map<int, Test<0>> meh;
}
