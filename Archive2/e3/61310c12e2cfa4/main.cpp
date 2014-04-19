using namespace std;

#include <string>
#include <algorithm>

typedef std::pair<short, std::string> Pair;

struct Cmp 
{
    bool operator()(Pair const& a, Pair const& b) const { return a.second < b.second; };
    bool operator()(Pair const& a, std::string const& b) const { return a.second < b; };
    bool operator()(std::string const& a, Pair const& b) const { return a < b.second; };
};

#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    std::vector<Pair> vec = { 
        { 1, "aap" }, 
        { 2, "zus" }, 
        { 3, "broer" }.
        { 42, "zus" }, 
    };

    Cmp cmp;
    std::sort(vec.begin(), vec.end(), cmp);

    auto range = std::equal_range(vec.begin(), vec.end(), std::string("zus"), cmp);

    for(auto it = range.first; it!= range.second; ++it)
       std::cout << it->first << ": " << it->second << "\n";
}

