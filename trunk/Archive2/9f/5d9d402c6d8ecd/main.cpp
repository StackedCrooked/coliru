#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace qi  = boost::spirit::qi;
namespace phx = boost::phoenix;

template <typename T, typename ElementParser = typename boost::spirit::traits::create_parser<T>::type>
void do_test(std::string const& input, 
        T const& start_value = std::numeric_limits<T>::lowest(),
        ElementParser const& element_parser = boost::spirit::traits::create_parser<T>::call())
{
    using It = std::string::const_iterator;

    std::vector<T> data;
    T max_value = start_value;

    It it = input.begin(), end = input.end();
    bool ok;
    
    {
        using namespace qi;
        using phx::if_;

        auto _running_max = phx::ref(max_value);

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunsequenced"
        ok = qi::phrase_parse(it, end, 
               eps             [ _running_max = start_value ]
            >> *element_parser [ if_(_1>_running_max) [_running_max=_1], _pass = true ],
            qi::space, data);
#pragma clang diagnostic pop
    }

    if (ok) {
        std::cout << "Parse success: " << data.size() << " elements with maximum of " << max_value << "\n";
        std::copy(data.begin(), data.end(), std::ostream_iterator<T>(std::cout << "\t values: ", " "));
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
