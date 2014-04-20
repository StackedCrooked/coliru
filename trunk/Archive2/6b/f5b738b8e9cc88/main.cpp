using namespace std;

#include <utility>
#include <vector>
#include <string>
#include <algorithm>

typedef std::pair<short, std::string> Pair;

struct Cmp 
{
    bool operator()(Pair const& a, Pair const& b) const { return a.second < b.second; };
    bool operator()(Pair const& a, std::string const& b) const { return a.second < b; };
    bool operator()(std::string const& a, Pair const& b) const { return a < b.second; };
};

int main()
{
    std::vector<Pair> vec = { 
        { 1, "aap" }, 
        { 2, "zus" }, 
        { 3, "broer" }
    };

    Cmp cmp;
    std::sort(vec.begin(), vec.end(), cmp);

    auto it = std::binary_search(vec.begin(), vec.end(), std::string("zus"), cmp);

    std::cout << it->first << ": " << it->second << "\n";
}

