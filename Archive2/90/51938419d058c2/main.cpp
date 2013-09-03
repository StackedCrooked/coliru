#include "boost/spirit/include/karma.hpp"

namespace karma = boost::spirit::karma;
using It = boost::spirit::ostream_iterator;

int main( int argc, char* argv[] )
{
    const std::vector<float> input { 1.0f, 2.0f };

    using namespace karma;
    rule<It, boost::optional<float>()> floatRule      = double_ | "0.0";
    rule<It, std::vector<float>(), space_type> output = -floatRule << -floatRule << -floatRule;

    std::cout << format_delimited(output, space, input);
}
