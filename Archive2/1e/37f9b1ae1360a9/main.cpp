//#define BOOST_SPIRIT_DEBUG
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace qi = boost::spirit::qi;
namespace phx = boost::phoenix;

using Iterator = std::string::const_iterator;

using attribType = std::string;

struct Parser : qi::grammar<Iterator, attribType(), qi::space_type>
{
   public:
     Parser() : Parser::base_type(group)
     {
         using namespace qi;
         
         name   %= lexeme [ +alnum ];
         names  %= +(name >> (&lit(')') | eps [ phx::push_back(_val, ' ') ]));
         group  %= '(' >> (group | names) >> ')';

         BOOST_SPIRIT_DEBUG_NODES((name)(names)(group))
     }

  private:
    typedef boost::spirit::qi::rule<Iterator, attribType(), qi::space_type> Rule;
    Rule group, names, name;
};


int main()
{
    std::string const input = "(  my   test1  ) (my  test2)";

    auto f(input.begin()), l(input.end());

    Parser p;

    std::vector<attribType> data;
    bool ok = qi::phrase_parse(f, l, *p, qi::space, data);

    if (ok)
    {
        std::cout << "Parse success\n";
        for(auto const& term : data)
            std::cout << "Term: '" << term << "'\n";
    }
    else
    {
        std::cout << "Parse failed\n";
    }

    if (f!=l)
        std::cout << "Remaining unparsed input: '" << std::string(f,l) << "'\n";
}
