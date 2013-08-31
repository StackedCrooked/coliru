#include <boost/fusion/adapted.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>

namespace qi    = boost::spirit::qi;
namespace karma = boost::spirit::karma;

namespace ast
{
    typedef boost::variant <int, double, std::string>  value; 
    typedef std::vector    <value>                     ordered_pair; 

    typedef boost::variant <value, ordered_pair>       pair_value; 
    typedef std::map       <std::string, pair_value>   pairs; 
    typedef std::pair      <std::string, pair_value>   pair; 

    typedef std::map       <std::string, pairs>        sections; 
    typedef std::pair      <std::string, pairs>        section; 
}

template <typename iterator, typename Skipper>
struct Grammar: qi::grammar<iterator, Skipper, ast::sections()>
{
    private:
        qi::rule<iterator, std::string()> key, string, section_name;
        qi::rule<iterator, ast::value()> value;

        qi::rule<iterator, Skipper, std::vector<ast::value>()> ordered_pair;
        qi::rule<iterator, Skipper, ast::pair()> pair;
        qi::rule<iterator, Skipper, ast::section()> section;
        qi::rule<iterator, Skipper, ast::sections()> start;
    public:
        Grammar() : Grammar::base_type(start)
        {
            using qi::char_;
            using qi::lit;
               
            key = 
                +char_("a-z")
                ;

            string = 
                   char_('"') 
                >> *~char_('"') 
                >> char_('"')
                ;

            section_name = 
                  qi::raw [ char_('#') >> qi::int_ ] // keep the matched int as a string
                | char_('%') >> +char_("a-z")
                ;

            value = qi::lexeme [
                  qi::int_ >> !lit('.') // if a dot follows prefer double_
                | qi::double_ 
                | string
                ];

            ordered_pair = 
                   '('
                >> (-value % ',') 
                >> ')'
                ;

            pair = 
                key >> '=' >> (value|ordered_pair)
                ;

            section = 
                section_name 
                >> '{' >> *pair >> '}' // allow empty {}
                ;

            start = +section;
        }
};

namespace debug
{
    template <typename Attr>
        using Karma = karma::rule<boost::spirit::ostream_iterator, Attr()>;

    static const Karma<ast::value>               value = karma::int_ | karma::double_ | karma::string;
    static const Karma<ast::ordered_pair> ordered_pair = '(' << (value % ", ") << ')';
    static const Karma<ast::pair_value>     pair_value = ordered_pair | value;
    static const Karma<ast::pair>                 pair = "\t" << karma::string << " = " << pair_value << "\n";
    static const Karma<ast::section>           section = karma::string << "\n{\n" << *pair << "}\n";
}

int main()
{
    const std::string input = 
        "#123 \n"
        "{ \n"
        "    int=4 double=3.14 \t\t\t\n"
        "    s=\"hello world\" } \n"
        "%foobar \n"
        "{ \n"
        "    ordered=(4, 3.14, \n"
        "           \"good\nbye\"\n" // note embedded newline
        "           , -42)\n"
        "}\n"
        ;
    auto f(begin(input)), l(end(input));

    typedef decltype(f) It;
    Grammar<It, qi::space_type> p;

    ast::sections parsed;
    bool ok = qi::phrase_parse(f, l, p, qi::space, parsed);

    if (ok)
    {
        std::cout << "Parse success\n";
        std::cout << karma::format(*debug::section, parsed);
    } else
    {
        std::cout << "Parse failed\n";
    }

    if (f!=l)
        std::cout << "\nRemaing unparsed: '" << std::string(f,l) << "'\n";

    return ok? 0 : 1;
}
