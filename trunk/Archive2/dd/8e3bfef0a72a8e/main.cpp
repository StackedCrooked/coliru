#include <algorithm>
#include <vector>

template <typename C, typename V/* = typename C::value_type*/>
   size_t index_of(C const& c, V const v)
{
    const auto f(begin(c)), l(end(c));

    auto match = std::find(f, l, v);
    return (l==match) ? -1 : std::distance(f, match);
}

template <typename C, typename Pred>
   size_t index_if(C const& c, Pred&& pred)
{
    const auto f(begin(c)), l(end(c));

    auto match = std::find_if(f, l, std::forward<Pred>(pred));
    return (l==match) ? -1 : std::distance(f, match);
}

int main()
{
    struct X { int ID; };
    const std::vector<X> v { {1},{2},{3},{25},{4},{5},{6},{42} };
    return index_if(v, [](X const& x) { return x.ID == 25; });
}
