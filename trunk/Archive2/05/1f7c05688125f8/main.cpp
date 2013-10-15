#include <boost/phoenix/phoenix.hpp>
#include <boost/phoenix/function/adapt_function.hpp>
#include <map>
#include <string>

namespace detail
{
    template <typename Pair, typename First = typename std::remove_reference<Pair>::type::first_type> 
    struct first_type {
        typedef First type;
    };
    
    template <typename Pair>
    typename first_type<Pair>::type first_impl(Pair const& p){
        return p.first;
    }
}

BOOST_PHOENIX_ADAPT_FUNCTION(typename detail::first_type<A0>::type, first, detail::first_impl, 1)

#include <algorithm>
#include <iostream>

int main()
{
    using namespace boost::phoenix::arg_names;
    using boost::phoenix::bind;

    std::map<std::string, int> const m { 
        { "one",   1 },
        { "two",   2 },
        { "three", 3 },
        { "four",  4 }
    };

    std::for_each(begin(m), end(m), std::cout << first(arg1) << "\n");
}
