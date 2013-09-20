#include <map>
#include <vector>

template <typename KeyIt, typename MapIt, typename OutIt>
    OutIt iterValues(KeyIt kbegin, KeyIt kend,
            MapIt mbegin, MapIt mend,
            OutIt out)
{
    while (kbegin!=kend && mbegin!=mend)
    {
        if (*kbegin < (mbegin->first))
            ++kbegin;
        else if (*kbegin > (mbegin->first))
            ++mbegin;
        else 
        {
            *out++ = mbegin->second;
            ++mbegin;
            ++kbegin;
        }
    }

    // optionally: 
    //if (kbegin!=kend) throw "Key(s) not found!";
    return out;
}

#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <set>

int main()
{
    const std::map<int, std::string> m { 
        { 1, "one" },
        { 2, "two" },
        { 3, "three" },
        { 8, "eight" },
        { -12, "minus twelve" },
        { -24, "minus twenty four" },
        { -36, "minus thirty six" }
    };

    // with a vector: sort first
    {
        std::vector<int> v { 1,8,-24 };
        std::sort(begin(v), end(v));

        iterValues(begin(v), end(v),
                begin(m), end(m),
                std::ostream_iterator<std::string>(std::cout, "\n"));
    }

    // better idea: make it a set! set is self-ordering
    {
        const std::set<int> s { 1,8,-24 };
        iterValues(begin(s), end(s),
                begin(m), end(m),
                std::ostream_iterator<std::string>(std::cout, "\n"));
    }
}
