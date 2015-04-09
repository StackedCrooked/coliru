//#include <boost/range.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/adaptors.hpp>
#include <vector>
#include <map>

template <typename Pred> auto by_key(Pred pred) {
    return [pred](auto const& p) { return pred(p.first); };
}

int main()
{
    using namespace boost::adaptors;

    std::map<int, std::string> m { {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"} };
    auto is_odd = [](int i) { return i%2==1; };

    // either using simple ranges
    auto r = keys(m) | filtered(is_odd) | transformed([&](auto i) { return m[i]; });
    std::vector<std::string> v(r.begin(), r.end());

    // or
    boost::copy(
            m | filtered(by_key(is_odd)) | map_values,
            back_inserter(v));


    // mix and match
    for (auto& s : m | filtered(by_key(is_odd)) | map_values)
        std::cout << s << "\n";
}
