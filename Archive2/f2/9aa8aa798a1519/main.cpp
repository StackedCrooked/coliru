#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <iostream>
#include <fstream>
#include <string>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace qi  = boost::spirit::qi;
namespace phx = boost::phoenix;

static const std::string B_condition = "INLE";

void process_line(std::vector<int> const& values, std::string const& kind)
{
    if (kind == "INLE")
    {
        std::cout << "Column 1: " << values[0] << "\n";
    }
}

int main()
{
    std::ifstream myfile("ramp.bnd");
    myfile.unsetf(std::ios::skipws);

    boost::spirit::istream_iterator f(myfile), l;

    using namespace qi;
    bool ok = phrase_parse(f, l,
            (repeat(7) [ int_ ] >> as_string[lexeme[+(char_ - eol)]])
                [ phx::bind(process_line, _1, _2) ]
            % eol, // supports CRLF and LF
            blank);

    if (!ok)
        std::cerr << "Parse errors\n";
    if (f!=l)
        std::cerr << "Remaing input: '" << std::string(f,l) << "'\n";
}
