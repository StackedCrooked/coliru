#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/format.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <cstdint>

namespace qi  = boost::spirit::qi;
namespace phx = boost::phoenix;

typedef std::vector<double> line_t;
typedef std::vector<line_t> lines_t;

template <typename Iterator>
struct sfparser : public qi::grammar<Iterator, lines_t(), qi::blank_type>
{
    sfparser () : sfparser::base_type(start)
    {
        using namespace qi;

        start = line % eol;
        line  = lit("SCALE") >> "FACTORS" >> *(double_|'.');
    }

  private:
    qi::rule<Iterator, lines_t(), qi::blank_type> start;
    qi::rule<Iterator, line_t(), qi::blank_type > line;
};

int main()
{
    std::string const input = " SCALE FACTORS      16.      0.0     0.0     0.0     0.0      .\n"
        "SCALE FACTORS      30.       .       .       .       .       .\n"
        "  SCALE FACTORS     256.      10.0     20.0     30.0    .\n";

    std::string::const_iterator f = input.begin();
    std::string::const_iterator l = input.end();
    sfparser<std::string::const_iterator> grammar;

    lines_t data;
    if (qi::phrase_parse (f, l, grammar, qi::blank, data))
    {
        std::cout << "Parsed " << data.size() << " lines\n";
        for (auto& line : data)
        {
            std::cout << "[SCALE FACTORS] ";
            for (auto d : line)
                std::cout << d << " ";

            std::cout << "\n";
        }
    }
    else
    {
        std::cout << "Failed\n";
    }

    if (f!=l)
        std::cout << "Remaining input: '" << std::string(f,l) << "'\n";
}
