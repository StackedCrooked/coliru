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

    Map::const_iterator byKeyFirst(Map const& map, int target)
    {
        // you can just find the first match, Pair is already sorted by `first`, then `second`:
        auto const e = end(map);
        auto lbound = lower_bound(begin(map), e, ByKeyFirst { target });
        if (lbound != e && lbound->first.first == target)
            return lbound;
        return e;
    }
}

#include <iostream>

int main()
{
    const Map myMap { 
        { { 1, 200 }, {} },
        { { 1, 202 }, {} },
        { { 2, 198 }, {} },
        { { 2, 207 }, {} },
    };

    auto match = byKeyFirst(myMap, 2);

    if (end(myMap) != match)
        std::cout << "Matching key: (" << match->first.first << "," << match->first.second << ")\n";
}
