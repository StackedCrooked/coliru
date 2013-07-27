#include <vector>
#include <set>
#include <list>
#include <algorithm>
#include <iterator>
#include <iostream>

// simple, but horrific performance
template <typename C, typename T = typename C::value_type> std::list<T> simple(C const& input)
{
    std::set<T> dupes; // optimization, dupes.find(x) in O(log n)
	for (auto it = begin(input); it != end(input); ++it)
	{
		if ((end(dupes) == dupes.find(*it)) // optimize by reducing find() calls
	     && (std::count(it, end(input), *it) > 1))
		{
			dupes.insert(dupes.end(), *it);
		}
	}
	
	return {begin(dupes), end(dupes)};
}

// alternative
template <typename C, typename T = typename C::value_type> std::list<T> adjacent_search(C input)
{
	std::sort(begin(input), end(input));

	static const auto eq = std::equal_to<T>{};
	static const auto neq= std::not2(eq);

	std::list<T> dupes;

	auto end_streak = begin(input);
	auto dupe_at    = std::adjacent_find(end_streak, end(input), eq);

	for(auto end_streak=begin(input);
	    (dupe_at = std::adjacent_find(end_streak, end(input), eq)) != end(input);
		end_streak = std::adjacent_find(dupe_at, end(input), neq))
	{
		dupes.insert(dupes.end(), *dupe_at);
	}

	return dupes;
}

template <typename T>
void print(std::string const& caption, std::list<T> const& list)
{
	std::copy(begin(list), end(list), std::ostream_iterator<std::string>(std::cout << "\n" << caption << ":\t", " "));
}


int main()
{
	const std::vector<std::string> input = { "unsorted", "containing", "optional", "unsorted", "duplicate", "duplicate", "values" };

	print("simple",          simple(input));
	print("adjacent_search", adjacent_search(input));

	std::cout << "\n";
}
