#include <iostream>
#include <fstream>
#include <boost/array.hpp>
#include <boost/spirit/include/qi.hpp>

namespace qi = boost::spirit::qi;

int main() {
    using Matrix = std::vector<std::vector<long> >;
    std::vector<Matrix> matrices;

    std::ifstream vl("PIXA.txt");
    boost::spirit::istream_iterator f(vl >> std::noskipws), l;

    if (qi::phrase_parse( f,l, ("J" >> qi::eol >>
                    +qi::long_ % qi::eol >>
                    qi::eol) % qi::eol, qi::blank, matrices))
    {
        std::cout << "Parsed ok\n";
        for (auto const& matrix : matrices)
        {
            std::cout << "\n\nJ";
            for (auto const& row : matrix)
                std::copy(row.begin(), row.end(), std::ostream_iterator<long>(std::cout << "\n", "\t"));
        }
    } else
        std::cout << "Parse failure\n";

    if (f!=l)
        std::cout << "Remaining input: '" << std::string(f,l) << "'\n";
}
