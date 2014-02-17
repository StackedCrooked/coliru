#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/qi_match.hpp>

namespace qi = boost::spirit::qi;
namespace karma = boost::spirit::karma;

int main()
{
    std::vector<std::vector<double>> data;

    std::stringstream tmp_stream(
            "123 45 inf -inf nan .7e-99\n"
            "42\n"
            "-1");

    if (tmp_stream >> std::noskipws >> qi::phrase_match((+qi::double_) % qi::eol, qi::blank, data))
    {
        std::cout << karma::format((karma::double_ % ", ") % karma::eol, data) << "\n";
    }
}
