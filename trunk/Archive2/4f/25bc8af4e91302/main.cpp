#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <map>

struct Tmp
{
    Tmp(int p)
        : v(p)
    {}
    Tmp(const Tmp& other)
        : v(other.v)
    {
        std::cout << "Tmp::Tmp(const Tmp& other)" << std::endl;
    }
    int v;
};

int main()
{
    std::map<std::string, Tmp> v;
    v.insert(std::make_pair("1", Tmp(1)));
	v.insert(std::make_pair("2", Tmp(2)));
	v.insert(std::make_pair("3", Tmp(3)));
	v.insert(std::make_pair("4", Tmp(4)));
	v.insert(std::make_pair("5", Tmp(5)));

    std::cout << "======" << std::endl;

    auto p = std::min_element(begin(v), end(v), 
		  [] (const std::pair<std::string, Tmp>& a,
			  const std::pair<std::string, Tmp>& b)
			{ 
			  return a.second.v < b.second.v; 
			});
    std::cout << p->second.v << std::endl;
}