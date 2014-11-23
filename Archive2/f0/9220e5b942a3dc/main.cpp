#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <iostream>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/mpl/bool.hpp>
#include <map>

namespace qi = boost::spirit::qi;
namespace phx = boost::phoenix;

struct MyContainer {
    typedef std::pair<int, int> Pair;
    typedef std::map<int, int>  Map;

    Map data;
    double number;
};

template <typename It, typename Skipper = qi::blank_type>
struct grammar : qi::grammar<It, MyContainer(), Skipper> {
    grammar() : grammar::base_type(start) {
        update_number = '=' > qi::double_ [ qi::_r1 = qi::_1 ];
        map_entry     = qi::int_ > ';' > qi::int_;

        auto number = phx::bind(&MyContainer::number, qi::_val);
        auto data   = phx::bind(&MyContainer::data, qi::_val);

        start         = *(
            (   update_number(number) 
              | map_entry [ phx::insert(data, phx::end(data), qi::_1) ]
            )
            >> qi::eol);
    }

  private:
    qi::rule<It, void(double&),       Skipper> update_number;
    qi::rule<It, MyContainer::Pair(), Skipper> map_entry;
    qi::rule<It, MyContainer(),       Skipper> start;
};

int main() {
    //const char g_data[] = "1;2\n=1200\n3;4\n5;6\n";
    const char g_data[] = "1;2\n=1200\n3;4\n5;6\n";
    std::cout << "Parsing data:\n" << g_data << "\n";

    MyContainer result;

    typedef const char* It;
    It f = std::begin(g_data), l = std::end(g_data) - 1;

    grammar<It> g;

    bool ok = qi::phrase_parse(f, l, g, qi::blank, result);

    if (ok)
    {
        std::cout << "Parsed data:\n";
        std::cout << "Result: " << result.number << "\n";
        for (const auto& p : result.data) {
            std::cout << p.first << " ; " << p.second << '\n';
        }
    } else
        std::cout << "Parse failed\n";

    if (f!=l)
        std::cout << "Remaining input: '" << std::string(f,l) << "'\n";
}
