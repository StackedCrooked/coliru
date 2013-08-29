#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>

namespace qi    = boost::spirit::qi;

int main()
{
    std::cin >> std::noskipws;
    boost::spirit::istream_iterator f(std::cin), l;

    std::vector<float> vect;

    bool ok = qi::phrase_parse(f,l,
            ('v' >> qi::float_ >> qi::float_ >> qi::float_) % qi::eol,
            qi::blank,
            vect);

    if (ok)   
    {
        std::cout << "parse success\n";

        // only for verification output:
        using namespace boost::spirit::karma;
        std::cout << "parsed vect: \n" << format_delimited(columns(3) [ *auto_ ], ' ', vect) << "\n";
    }
    else std::cerr << "parse failed: '" << std::string(f,l) << "'\n";

    if (f!=l) std::cerr << "trailing unparsed: '" << std::string(f,l) << "'\n";
    return ok;
}
