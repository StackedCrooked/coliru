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

using runtime_signature = std::vector<std::type_index>;

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

template<class Iterator, class... Args>
Iterator dispatch(Iterator begin, Iterator end, Args... args) {
    std::vector<runtime_signature> candidates;
    
    for (auto it = begin; it != end; ++it)
    {
        auto& potential_candidate = *it;
        
        if(potential_candidate.size() == sizeof...(Args))
        {
            using boost::fusion::all;
            using boost::fusion::transform;
            boost::phoenix::arg_names::arg1_type identity;

            if (all(
                transform(
                    detail::fusion_tie<sizeof...(Args)>::call(potential_candidate), 
                    std::make_tuple(args...),
                    [](std::type_index runtime_arg, auto static_arg) {
                        return runtime_arg == typeid(decltype(static_arg));
                    }
                ), identity))
            {
                return it;
            }
        }
    }

    throw std::runtime_error("no matching candidates");
}

int main() {
    std::vector<runtime_signature> candidates;
    
    candidates.push_back({ typeid(int), typeid(double) });
    candidates.push_back({ typeid(std::string), typeid(float) });

    std::cout << "Getting first overload: \n";
    assert(candidates.begin() == dispatch(candidates.begin(), candidates.end(), 1, 2.0));
    
    std::cout << "Getting second overload: \n";
    assert(candidates.begin()+1 == dispatch(candidates.begin(), candidates.end(), std::string("hello world"), 69.0f));

    std::cout << "Getting failure: \n";
    try {
        dispatch(candidates.begin(), candidates.end(), std::string("hello world"), 69.0f, "willy wonka is a nasty man"); // runtime error - no candidates
    } catch (std::exception const& e)
    {
        std::cout << "Error: " << e.what() << "\n";
    }
    
    return 0;
}

