#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace qi  = boost::spirit::qi;
namespace phx = boost::phoenix;

using vector_and_max = std::pair<std::vector<int>, int>;

int maximum(int a, int b) {
    return std::max(a, b);
}

BOOST_PHOENIX_ADAPT_FUNCTION(int, maximum_, maximum, 2)

template <typename It, typename Skipper = qi::space_type>
struct max_parser : qi::grammar<It, vector_and_max(), Skipper> {
    max_parser(int const& start_value) : max_parser::base_type(start) {
        using namespace qi;
        using phx::if_;

        _a_type running_max;

        vector_with_max %= 
               eps   [ running_max = start_value ]
            >> *int_ [ running_max = maximum_(running_max, _1) ]
            >> attr(running_max)
            ;

        start = vector_with_max;
    }

  private:
    qi::rule<It, vector_and_max(), Skipper> start;
    qi::rule<It, vector_and_max(), Skipper, qi::locals<int> > vector_with_max;
};

void do_test(std::string const& input, int start_value = std::numeric_limits<int>::lowest())
{
    using It = std::string::const_iterator;

    vector_and_max data;
    It it = input.begin(), end = input.end();
    bool ok = qi::phrase_parse(it, end, max_parser<It>(start_value), qi::space, data);

    if (ok) {
        std::cout << "Parse success: " << data.first.size() << " elements with maximum of " << data.second << "\n";
        std::copy(data.first.begin(), data.first.end(), std::ostream_iterator<int>(std::cout << "\t values: ", " "));
        std::cout << "\n";
    } else {
        std::cout << "Parse failed\n";
    }

    if (it != end)
        std::cout << "Remaining unparsed: '" << std::string(it,end) << "'\n";
}

int main() {
    do_test(" 1 99 -1312 4 1014");
}
