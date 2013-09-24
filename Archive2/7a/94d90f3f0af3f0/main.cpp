#include <map>
#include <tuple>
#include <limits>

using namespace std;

struct A {};

using Pair = pair<int,int>;
using Map  = map<Pair, A>;

namespace /*anon*/
{
    struct ByKeyFirst final { int value; };
    inline bool operator<(Map::value_type const& v, ByKeyFirst target) { return v.first.first < target.value; }
}

#include <iostream>

int main()
{
    Pair q, b;
    if(q < b) return 0;

    const Map myMap { 
        { { 1, 200 }, {} },
        { { 1, 202 }, {} },
        { { 2, 198 }, {} },
        { { 2, 207 }, {} },
    };

    // you can just find the first match, Pair is already sorted by `first`, then `second`:
    const int target = 2;
    auto lbound = lower_bound(begin(myMap), end(myMap), ByKeyFirst{target}); 

    for (auto it = lbound;  (it != end(myMap) && (it->first.first == target)); ++it)
        std::cout << "Matching key: (" << it->first.first << "," << it->first.second << ")\n";
}
