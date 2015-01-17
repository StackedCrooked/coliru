#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/finder.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <boost/phoenix.hpp>
#include <boost/phoenix/stl.hpp>
#include <boost/utility/string_ref.hpp>
#include <iostream>

using namespace boost::algorithm;
namespace phx = boost::phoenix;
using namespace phx::arg_names;
using boost::adaptors::transformed;

int main() {
    std::string input = "1;3;5;7";

    using boost::string_ref;
    using R = boost::iterator_range<std::string::const_iterator>;
    using V = std::vector<R>;
    V v;

    // jsut the iterator ranges:
    for (auto&& r : iter_split(v, input, token_finder(is_any_of(";"))))
        std::cout << r << "\n";

    // using a lambda to create the string_refs:
    for (string_ref&& r : iter_split(v, input, token_finder(is_any_of(";"))) 
            | transformed([](R const& r){return string_ref(&*r.begin(), r.size());}))
        std::cout << r << "\n";

    // c++03 version:
    for (string_ref&& r : iter_split(v, input, token_finder(is_any_of(";"))) 
            | transformed(phx::construct<string_ref>(&*phx::begin(_1), phx::size(_1))))
        std::cout << r << "\n";
}
