#include <iostream>
#include <map>
#include <algorithm>
#include <type_traits>
#include <utility>
#include <boost/fusion/include/map.hpp>
#include <boost/fusion/include/pair.hpp>
#include <boost/fusion/sequence/intrinsic/value_at_key.hpp>
#include <boost/fusion/sequence/intrinsic/at_key.hpp>
#include <boost/fusion/container/map.hpp>
#include <boost/fusion/algorithm.hpp>

struct Age{};
struct Weight{};

using Key = boost::fusion::pair<Age, int>;
using Value = boost::fusion::pair<Weight, int>;
using map_type = boost::fusion::map<Key, Value>;

auto cmp = [](const Key& a, const Key& b) ->bool {
    return a.second < b.second;
};

template <class K, class It>
typename std::remove_reference<typename boost::fusion::result_of::at_key<map_type, K>::type>::type
get(It it) {
    map_type x{it->first, it->second};
    return boost::fusion::at_key<K>(x);
}

int main() {
    std::map<Key, Value, decltype(cmp)> m(cmp);
    m[30] = 90;
    auto it = m.find(30);
    std::cout << get<Age>(it) << ", " << get<Weight>(it) << std::endl;

    map_type x(it->first, it->second);
    std::cout << boost::fusion::at_key<Age>(x) << std::endl; // reference preserved
}
