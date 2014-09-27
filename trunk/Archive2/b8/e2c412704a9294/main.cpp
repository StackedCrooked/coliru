#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <map>

struct Tmp
{
    explicit Tmp(int p = 0)
        : v(p)
    {}
    Tmp(const Tmp& other)
        : v(other.v)
    {
        std::cout << "Tmp::Tmp(const Tmp& other). v:" << v << std::endl;
    }
    
    Tmp& operator=(const Tmp& other) = default;  
    Tmp(Tmp&& other) = default;
    Tmp& operator=(Tmp&& other) = default;    
    
    int v;
};

int main()
{
    std::vector<Tmp> v;
    v.emplace_back(Tmp{1});
    v.emplace_back(Tmp{2});
    v.emplace_back(Tmp{3});
    
    std::cout << "= find min element in vector ========================================" << std::endl;
    auto p = std::min_element(begin(v), end(v), [] (const Tmp& a, const Tmp& b) { return a.v < b.v; });
    std::cout << "min element: " << p->v << std::endl;
    std::cout << std::endl;

    std::map<std::string, Tmp> m;
    m.emplace(std::make_pair("1", Tmp(1)));
    m.emplace(std::make_pair("2", Tmp(2)));
    m.emplace(std::make_pair("3", Tmp(3)));                
    
    std::cout << "= find min element in map ========================================" << std::endl;
    auto p2 = std::min_element(begin(m), end(m), 
		  [] (const std::pair<std::string, Tmp>& a,
			  const std::pair<std::string, Tmp>& b)
			{ 
			  return a.second.v < b.second.v; 
			});
    std::cout << "min element: " << p2->second.v << std::endl;
}