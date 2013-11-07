#define BOOST_SPIRIT_DEBUG
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/support_line_pos_iterator.hpp>

namespace qi = boost::spirit::qi;

typedef boost::spirit::line_pos_iterator<std::string::const_iterator> pos_iterator_t;

template <typename Iterator, typename Skipper = qi::space_type>
struct ParseGrammar: public qi::grammar<Iterator, Skipper>
{
    ParseGrammar() : ParseGrammar::base_type(Module)
    {
        using namespace qi;

        Identifier = alpha >> *(alnum | '_');
        Module     = "import" >> Identifier >> "all" >> ';';

        BOOST_SPIRIT_DEBUG_NODES((Module)(Identifier))
    }

    qi::rule<Iterator, Skipper> Module;
    qi::rule<Iterator> Identifier;
};

int main()
{
   std::string const content = "import \r\n\r\nfoobar\r\n\r\n all; bogus";

   pos_iterator_t first(content.begin()), iter=first, last(content.end());

   ParseGrammar<pos_iterator_t> resolver;    //  Our parser
   bool ok = phrase_parse(iter, last, resolver, qi::space);

   std::cout << std::boolalpha;
   std::cout << "ok   : " << ok << std::endl;
   std::cout << "full : " << (iter == last) << std::endl;

   if(ok && iter==last)
   {
      std::cout << "OK: Parsing fully succeeded\n\n";
   }
   else
   {
      int line   = get_line(iter);
      int column = get_column(first, iter);
      std::cout << "-------------------------\n";
      std::cout << "ERROR: Parsing failed or not complete\n";
      std::cout << "stopped at: " << line  << ":" << column << "\n";
      std::cout << "remaining: '" << std::string(iter, last) << "'\n";
      std::cout << "-------------------------\n";
   }
   return 0;
}
