#include <iostream>
#include <string>
#include <vector>
#include <set>

int main()
{
    {
		std::string s = "Hello";
		std::cout << std::boolalpha << (decltype(s)::iterator() == s.end()) << std::endl;
		auto const it = s.end();
		s += "!";
		std::cout << std::boolalpha << (it == s.end()) << std::endl;
	}
	{
		std::vector<int> v = {1, 2, 3};
		std::cout << std::boolalpha << (decltype(v)::iterator() == v.end()) << std::endl;
		auto const it = v.end();
		v.push_back(4);
		std::cout << std::boolalpha << (it == v.end()) << std::endl;
	}
	{
		std::set<int> s = {1, 2, 2, 3};
		std::cout << std::boolalpha << (decltype(s)::iterator() == s.end()) << std::endl;
		auto const it = s.end();
		s.insert(4);
		std::cout << std::boolalpha << (it == s.end()) << std::endl;
	}
}
