////  #define BOOST_SPIRIT_DEBUG
#include <boost/spirit/include/qi.hpp>
#include <boost/variant/recursive_variant.hpp>

#include <iostream>
#include <fstream>

namespace client
{
    template <typename What> struct adl_wrapper {
        adl_wrapper(What&& w) : _w(std::forward<What>(w)) {}
        What&& _w;
        operator What&&() { return _w; }
    };

    typedef boost::make_recursive_variant<
            boost::variant<std::string, std::vector<boost::recursive_variant_> > 
        >::type tag_soup;

    namespace qi = boost::spirit::qi;

    template <typename It>
    struct parser : qi::grammar<It, tag_soup()>
    {
        parser() : parser::base_type(soup)
        {
            simple = +~qi::char_("><");
            nested = '<' >> *soup >> '>';
            soup   = nested|simple;

            BOOST_SPIRIT_DEBUG_NODES((simple)(nested)(soup))
        }
      private:
        qi::rule<It, std::string()>           simple;
        qi::rule<It, std::vector<tag_soup>()> nested;
        qi::rule<It, tag_soup()>              soup;
    };
}
namespace boost { // leverage ADL on variant<>
    static std::ostream& operator<<(std::ostream& os, std::vector<client::tag_soup> const& soup)
    {
        os << "<";
        std::copy(soup.begin(), soup.end(), std::ostream_iterator<client::tag_soup>(os));
        return os << ">";
    }
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        std::cerr << "Error: No input file provided.\n";
        return 1;
    }

    std::ifstream in(argv[1]);
    std::string const storage(std::istreambuf_iterator<char>(in), {}); // We will read the contents here.

    if (!(in || in.eof())) {
        std::cerr << "Error: Could not read from input file\n";
        return 1;
    }

    static const client::parser<std::string::const_iterator> p;

    client::tag_soup ast; // Our tree
    bool ok = parse(storage.begin(), storage.end(), p, ast);

    if (ok) std::cout << "Parsing succeeded\nData: " << ast << "\n";
    else    std::cout << "Parsing failed\n";

    return ok? 0 : 1;
}
