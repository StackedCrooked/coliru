#include <type_traits>
#include <iterator>

template <typename T, typename InputIterator, typename OutputIterator, typename Comparator>
void find_mismatches(InputIterator first, InputIterator last,
                     T const& val, OutputIterator out, Comparator comp)
{
    for (; first != last; ++first)
    {
        auto&& f = *first;
        if (!comp(f.second, val))
            *out++ = f;
    }
}

template <typename AssociativeCont, typename OutputIterator, typename Comparator>
void find_mismatches(AssociativeCont&& rng, typename std::remove_reference<AssociativeCont>::type::value_type const& val, OutputIterator out, Comparator comp)
{
    auto range = rng.equal_range(val.first);
    find_mismatches(range.first, range.second, val.second, out, comp);
}

template <typename AssociativeCont, typename OutputIterator>
void find_mismatches(AssociativeCont&& rng, typename std::remove_reference<AssociativeCont>::type::value_type const& val, OutputIterator out)
{
    auto range = rng.equal_range(val.first);
    find_mismatches(range.first, range.second, val.second, out, std::equal_to<decltype(val.second)>());
}

#include <vector>
#include <unordered_map>
#include <iostream>

int main()
{
    using namespace std;
    
    unordered_multimap<int, int> myset {
        {1,2},{1,5},{1,6},{2,4},{3,5},{4,6},{6,7},{6,8}
    };
    
    vector<decltype(myset)::value_type> vec;
    find_mismatches(myset, {1, 5}, back_inserter(vec));
    for (v : vec)
        std::cout << v.first << ' ' << v.second << '\n';
}
