#define BOOST_SPIRIT_DEBUG
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace qi        = boost::spirit::qi;

template <typename It, typename Skipper = qi::iso8859_1::space_type>
    struct Parser : qi::grammar<It, Skipper>
{
    Parser() : Parser::base_type(root)
    {
        using namespace qi::iso8859_1;

        braces  = 
            '{' >> qi::eps >> '}'
            ;
        str     = qi::lexeme [
                 '"'
              >> *~char_('"')
              >> '"'
            ]
            ;
        tolleaf = qi::lexeme [
                +(~char_("\"{}= \t\r\n"))
            ]
            ;
        leaf    = qi::lexeme [
                +(alnum | char_("-._:"))
            ]
            ;
        taglist = 
               '{'
            >> -str % tolleaf
            >> '}'
            ;
        object  = 
                 '{'
              >> *root
              >> '}'
            ;
        objlist = 
                 '{'
              >> *object
              >> '}'
            ;
        assign  = 
                 (leaf | str)
              >> '='
              >> (leaf | str | taglist | objlist | object) 
            ;
        root    = 
            +(assign | braces)
            ;

        BOOST_SPIRIT_DEBUG_NODES((root)(braces)(str)(tolleaf)(leaf)(taglist)(objlist)(object)(assign));
    }

  private:
    qi::rule<It, Skipper> root, braces, str, tolleaf, leaf, taglist, objlist, object, assign;
};

int main()
{
    typedef boost::spirit::istream_iterator It;
    std::cin.unsetf(std::ios::skipws);
    It f(std::cin), l;

    namespace iso8859_1 = qi::iso8859_1;
    Parser<It, iso8859_1::space_type> p;

    try
    {
        bool ok = qi::phrase_parse(f,l,p,iso8859_1::space);
        if (ok)   std::cout << "parse success\n";
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

