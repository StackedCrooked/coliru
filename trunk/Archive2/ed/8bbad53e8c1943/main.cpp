#include <boost/spirit/include/qi.hpp>

namespace qi    = boost::spirit::qi;

template <typename It, typename Skipper = qi::space_type>
    struct parser : qi::grammar<It, bool(), Skipper>
{
    parser() : parser::base_type(implicit_method_declaration)
    {
        using namespace qi;

        implicit_method_declaration = matches["abstract"];

        BOOST_SPIRIT_DEBUG_NODES((implicit_method_declaration));
    }

  private:
    qi::rule<It, bool(), Skipper> implicit_method_declaration;
};

bool doParse(const std::string& input)
{
    typedef std::string::const_iterator It;
    auto f(begin(input)), l(end(input));

    parser<It, qi::space_type> p;
    bool data;

    try
    {
        bool ok = qi::phrase_parse(f,l,p,qi::space,data);
        if (ok)   
        {
            std::cout << "parse success\n";
            std::cout << "data: " << data << "\n";
        }
        else      std::cerr << "parse failed: '" << std::string(f,l) << "'\n";

        if (f!=l) std::cerr << "trailing unparsed: '" << std::string(f,l) << "'\n";
        return ok;
    } catch(const qi::expectation_failure<It>& e)
    {
        std::string frag(e.first, e.last);
        std::cerr << e.what() << "'" << frag << "'\n";
    }

    return false;
}

int main()
{
    doParse("abstract");
    doParse("static final");
}
