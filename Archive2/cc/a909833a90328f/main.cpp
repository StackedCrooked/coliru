#include <type_traits>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <iostream>

//-----------------------------------------------------------------------------

template<typename F, typename T, typename A>
void make_ranges(F& from, T& to, A array)
{
	auto diff = array;
	std::sort(array.begin(), array.end());
	std::adjacent_difference(array.begin(), array.end(), diff.begin());

	std::vector<size_t> idx(array.size());
	std::iota(idx.begin(), idx.end(), 0);
	auto sep = [&diff] (size_t i) { return diff[i] > 1; };
	for(auto p = idx.begin(); p != idx.end();)
	{
		from.push_back(array[*p]);
		p = std::find_if(++p, idx.end(), sep);
		to.push_back(array[*(p - 1)]);
	}
}

//-----------------------------------------------------------------------------

template<typename S, typename I, typename J>
void print_range(S& stream, I i, J j)
{
    stream << *i;
	if (*j != *i)
		stream << "-" << *j;
}

template<typename S, typename F, typename T>
void print_ranges(S& stream, const F& from, const T& to)
{
	auto i = from.begin();
	auto j = to.begin();
	if (i != from.end())
		print_range(stream, i++, j++);
	while (i != from.end())
	{
		stream << ",";
		print_range(stream, i++, j++);
	}
}

//-----------------------------------------------------------------------------

template<typename A>
struct array_ranges : std::tuple<A> { using std::tuple<A>::tuple; };

template<typename A>
array_ranges<A> ranges(A&& a) { return array_ranges<A>{std::forward<A>(a)}; }

template<typename S, typename A>
S& operator<<(S& stream, const array_ranges<A>& ranges)
{
	typename std::decay<A>::type from, to;
	make_ranges(from, to, std::get<0>(ranges));
	print_ranges(stream, from, to);
	return stream;
}

//-----------------------------------------------------------------------------

template<typename S, typename T>
S& operator<<(S& stream, const std::vector<T>& array)
{
	for (auto& x : array)
		stream << x << " ";
	return stream;
}

int main ()
{
	std::vector<int> arr{1,2,3,4,5,7,7,8,8,8,10,15,10,11,12,88,87,86};
	std::cout << arr << std::endl;
	std::cout << ranges(arr) << std::endl;
}
