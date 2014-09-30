#include <type_traits>
#include <boost/fusion/container/map.hpp>
#include <boost/fusion/algorithm/iteration/fold.hpp>
#include <boost/fusion/algorithm/transformation/insert.hpp>
#include <boost/fusion/algorithm/transformation/join.hpp>
#include <boost/fusion/algorithm/transformation/erase_key.hpp>

int main()
{
    using namespace boost::fusion;
    map<
        pair<int, int>,
        pair<double, int>> m1;

    map<
        pair<bool, int>,
        pair<double, int>> m2;

    auto r = 
        as_map(
            fold(
                fold(m1, m2, [](auto accum, auto elem) { return erase_key<typename decltype(elem)::first_type>(accum); }),
                m1, 
                [](auto accum, auto elem) { return insert(accum, boost::fusion::end(accum), elem); }
            )); 

    static_assert(std::is_same<decltype(r), map<
            pair<int, int>,
            pair<double, int>,
            pair<bool, int>
            >>::value, "");
}

