#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace qi  = boost::spirit::qi;
namespace phx = boost::phoenix;

template <typename T>
    using vector_and_max = std::pair<std::vector<T>, T>;

template <typename It, typename T, typename Skipper = qi::space_type>
struct max_parser : qi::grammar<It, vector_and_max<T>(), Skipper> {
    template <typename ElementParser>
    max_parser(T const& start_value, ElementParser const& element_parser) : max_parser::base_type(start) {
        using namespace qi;
        using phx::if_;

        _a_type running_max;

        vector_with_max %= 
               eps    [ running_max = start_value ]
            >> *boost::proto::deep_copy(element_parser) 
                      [ if_(_1>running_max) [running_max=_1], _pass = true ]
            >> attr(running_max)
            ;

        start = vector_with_max;
    }

  private:
    qi::rule<It, vector_and_max<T>(), Skipper> start;
    qi::rule<It, vector_and_max<T>(), Skipper, qi::locals<T> > vector_with_max;
};

template <typename T, typename ElementParser = typename boost::spirit::traits::create_parser<T>::type>
void do_test(std::string const& input, 
        T const& start_value = std::numeric_limits<T>::lowest(),
        ElementParser const& element_parser = boost::spirit::traits::create_parser<T>::call())
{
    using It = std::string::const_iterator;

    vector_and_max<T> data;
    It it = input.begin(), end = input.end();
    bool ok = qi::phrase_parse(it, end, max_parser<It, T>(start_value, element_parser), qi::space, data);

    if (ok) {
        std::cout << "Parse success: " << data.first.size() << " elements with maximum of " << data.second << "\n";
        std::copy(data.first.begin(), data.first.end(), std::ostream_iterator<T>(std::cout << "\t values: ", " "));
        std::cout << "\n";
    } else {
        std::cout << "Parse failed\n";
    }

    if (it != end)
        std::cout << "Remaining unparsed: '" << std::string(it,end) << "'\n";
}

int main() {
    do_test<int>(" 1 99 -1312 4 1014");
    do_test<double>(" 1 NaN -4 7e3 7e4 -31e9");
    do_test<std::string>("beauty shall be in ze eye of the beholder", "", qi::as_string[qi::lexeme[+qi::graph]]);
}
