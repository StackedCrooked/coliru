#include <string>
#include <iostream>
#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/include/qi.hpp>

namespace qi = boost::spirit::qi;

namespace ast {
    struct fruit {
        std::string name;
        std::string color;

        friend std::ostream& operator<<(std::ostream& os, fruit const& f) { return os << f.name << " is " << f.color; }
    };
    struct person {
        std::string name;
        int age;

        friend std::ostream& operator<<(std::ostream& os, person const& p) { return os << p.name << " with age" << p.age << " has been seen!"; }
    };

    typedef boost::variant<fruit, person> record;
    typedef std::vector<record> records;
}

BOOST_FUSION_ADAPT_STRUCT(ast::fruit,
    (std::string, name)
    (std::string, color))

BOOST_FUSION_ADAPT_STRUCT(ast::person,
    (std::string, name)
    (int, age))

template <typename Iterator, typename Skipper = qi::space_type>
    struct MyGrammar : qi::grammar<Iterator, ast::records(), Skipper>
{
    MyGrammar() : MyGrammar::base_type(_start)
    {
        _text   = qi::lexeme [ *~qi::char_(",)]") ];
        _person = qi::lit('(') >> _text >> ',' >> qi::int_ >> ')';
        _fruit  = qi::lit('[') >> _text >> ',' >> _text >> ']';

        _start  = *(_fruit | _person);
    }

    qi::rule<Iterator, ast::records(), Skipper> _start;
    qi::rule<Iterator, ast::person(),  Skipper> _person;
    qi::rule<Iterator, ast::fruit(),   Skipper> _fruit;
    qi::rule<Iterator, std::string()>           _text;
};

int main()
{
    typedef std::string::const_iterator It;
    std::string const input("(jane, 23000)(david, 19)(mary, 30)[yello,100][green, 60.6][red, 30.5]");

    MyGrammar <It> my_grammar;

    It begin(input.begin()), end(input.end());

    ast::records data;
    if (qi::phrase_parse(begin, end, my_grammar, qi::space, data))
    {
        std::cout << "Parse success\n";
        for (auto& r : data)
            std::cout << r << "\n";
    }
    else
        std::cout << "Parse failed\n";

    if (begin != end)
        std::cout << "Remaining unparsed: '" << std::string(begin, end) << "'\n";
}
