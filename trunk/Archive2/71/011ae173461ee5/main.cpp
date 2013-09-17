#include <algorithm>

template <typename C, typename V/* = typename C::value_type*/>
   size_t index_of(C const& c, V const v)
{
    const auto f(begin(c)), l(end(c));
    auto match = std::find(f, l, v);
    return (l==match) ? -1 : std::distance(f, match);
}

#include <vector>

int main()
{
    const std::vector<int> v { 1,2,3,25,4,5,6,42 };
    return index_of(v, 25);
}
