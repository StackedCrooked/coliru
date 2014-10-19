#include <memory>
#include <cassert>
#include <iostream>
#include <typeindex>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <stdexcept>
#include <boost/fusion/adapted/std_tuple.hpp> //This feature is undocumented
#include <boost/fusion/include/tuple_tie.hpp>
#include <boost/fusion/include/all.hpp>
#include <boost/phoenix.hpp>
#include <boost/fusion/include/transform.hpp>
#include <boost/range/algorithm.hpp>

using runtime_signature = std::vector<std::type_index>;
using overload_set      = std::vector<runtime_signature>;

namespace detail
{
    // this could be done using some kind of indices tool that I'm too tired to think up now. 
    template <size_t N> struct fusion_tie;
    template <> struct fusion_tie<0> { 
        template <typename Vec> static boost::fusion::vector0<> call(Vec&) { return {}; }
    };
    template <> struct fusion_tie<1> { 
        template <typename Vec, typename V = typename Vec::value_type> 
            static boost::fusion::tuple<V> call(Vec& v) { return boost::fusion::tie(v[0]); }
    };
    template <> struct fusion_tie<2> { 
        template <typename Vec, typename V = typename Vec::value_type>
            static boost::fusion::tuple<V, V> call(Vec& v) { return boost::fusion::tie(v[0], v[1]); }
    };
    template <> struct fusion_tie<3> { 
        template <typename Vec, typename V = typename Vec::value_type>
            static boost::fusion::tuple<V, V, V> call(Vec& v) { return boost::fusion::tie(v[0], v[1], v[2]); }
    };

    // etc...
}

template<class Set, class... Args>
overload_set resolve_overloads(Set const& overloads, Args...) {
    overload_set candidates;
    
    using std::begin;
    using std::end;

    std::copy_if(begin(overloads), end(overloads), std::back_inserter(candidates), [](auto potential_candidate) -> bool {
        using boost::fusion::all;
        using boost::fusion::transform;
        boost::phoenix::arg_names::arg1_type identity;

        return potential_candidate.size() == sizeof...(Args) && all(
                transform(
                    detail::fusion_tie<sizeof...(Args)>::call(potential_candidate), 
                    std::tie(typeid(Args)...),
                    std::equal_to<std::type_index>()
                ), identity);
        });

    return candidates;
}

int main() {
    overload_set const candidates {
        { typeid(int), typeid(double) },
        { typeid(std::string), typeid(float) },
    };

    std::cout << "Getting first overload: \n";
    overload_set matching = resolve_overloads(candidates, 1, 2.0);
    assert(1 == matching.size());
    assert(matching.front() == candidates.front());
    
    std::cout << "Getting second overload: \n";
    matching = resolve_overloads(candidates, std::string("hello world"), 69.0f);
    assert(1 == matching.size());
    assert(matching.front() == candidates.back());

    std::cout << "Getting empty set: \n";
    matching = resolve_overloads(candidates, std::string("hello world"), 69.0f, "willy wonka is a nasty man");
    assert(matching.empty());

    std::cout << "All done\n";
}

