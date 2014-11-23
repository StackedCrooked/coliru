#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/fusion/adapted/std_pair.hpp>
#include <map>

namespace qi = boost::spirit::qi;
namespace phx = boost::phoenix;

int main() {
    typedef const char* It;
    const char g_data[] = "1;2\n=1200\n3;4\n5;6\n";
    std::cout << "Parsing data:\n" << g_data << "\n";

    It f = std::begin(g_data), l = std::end(g_data) - 1;

    std::map<int, int> data;
    double number;

    bool ok = qi::phrase_parse(f, l, 
           *(
                (qi::omit['=' > qi::double_ [phx::ref(number)=qi::_1]] 
              | (qi::int_ > ';' > qi::int_)
            ) >> qi::eol)
            , qi::blank, data);

    if (ok)
    {
        std::cout << "Parsed data:\n";
        std::cout << "Result: " << number << "\n";
        for (const auto& p : data) {
            std::cout << p.first << " ; " << p.second << '\n';
        }
    } else
        std::cout << "Parse failed\n";

    if (f!=l)
        std::cout << "Remaining input: '" << std::string(f,l) << "'\n";
}
