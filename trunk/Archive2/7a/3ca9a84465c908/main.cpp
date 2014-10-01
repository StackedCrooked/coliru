#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <set>

template<typename T>
bool seti(std::set<T> &u, T val)
{
    auto x = u.insert(val);
	std::cout << "insert " << val << ": " << std::boolalpha << x.second << "\n";
	return x.second;
}

template<typename T>
struct Seen
{
	Seen() { std::cout << "Seen::default construct\n";}
	Seen(Seen const &s): items(s.items) { std::cout << "Seen::copy construct\n";}
	Seen(Seen &&s): items(std::move(s.items)) { std::cout << "Seen::move construct\n"; }
	Seen & operator=(Seen const &s) { items = s.items; std::cout << "Seen::copy-assignment\n"; return *this; }
	Seen & operator=(Seen &&s) { items = std::move(s.items); std::cout << "Seen::move-assignment\n"; return *this; }
	~Seen() { std::cout << "Seen::destruct\n"; }

	std::set<T> items;
	bool operator()(T t)
	{
		//return !items.insert(t).second;
		return !seti<T>(items, t);
	}
};

int main()
{
	std::vector<int> t = { 9, 3, 9, 5, 3, 16 };

	Seen<int> s;
	auto new_end = std::remove_if( std::begin(t), std::end(t), s );
	//auto new_end = my_remove_if( std::begin(t), std::end(t), s );

	for (auto it = std::begin(t); it != new_end; ++it)
		std::cout << *it << " ";

	std::cout << std::endl;
}
