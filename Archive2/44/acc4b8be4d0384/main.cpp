#define BOOST_SPIRIT_DEBUG
#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace qi  = boost::spirit::qi;
namespace phx = boost::phoenix;

namespace Ast {
    using boost::optional;
    struct date { unsigned day, month, year; };
    struct time { unsigned hours, minutes, seconds; };
    struct date_time { date date_part; optional<time> time_part; };

    struct period { date_time start, end; };
}

BOOST_FUSION_ADAPT_STRUCT(Ast::date, (unsigned,day)(unsigned,month)(unsigned,year))
BOOST_FUSION_ADAPT_STRUCT(Ast::time, (unsigned,hours)(unsigned,minutes)(unsigned,seconds))
BOOST_FUSION_ADAPT_STRUCT(Ast::date_time, (Ast::date,date_part)(Ast::optional<Ast::time>, time_part))
BOOST_FUSION_ADAPT_STRUCT(Ast::period, (Ast::date_time,start)(Ast::date_time,end))

template <typename Iterator>
struct Parser : qi::grammar<Iterator, Ast::period(), qi::space_type>
{
    int test;
    Parser() : Parser::base_type(period_)
    {
        using namespace qi;

        static const int_parser<unsigned, 10, 2, 2> _2digit = {};
        static const int_parser<unsigned, 10, 4, 4> _4digit = {};

        time_      = _2digit >> ":" >> _2digit >> ":" >> _2digit;
        date_      = _2digit >> "." >> _2digit >> "." >> _4digit;
        date_time_ = date_ >> -time_;
        period_    = date_time_ >> "," >> date_time_;

        BOOST_SPIRIT_DEBUG_NODES((period_)(time_)(date_))
    }

  private:
    qi::rule<Iterator, Ast::period(),    qi::space_type> period_;
    qi::rule<Iterator, Ast::date(),      qi::space_type> date_;
    qi::rule<Iterator, Ast::time(),      qi::space_type> time_;
    qi::rule<Iterator, Ast::date_time(), qi::space_type> date_time_;
};


int main()
{
    using It = std::string::const_iterator;

    Parser<It> parser;
    std::string input("10.06.2014 10:00:15, 11.07.2014");

    It f(input.begin()), l(input.end());

    Ast::period parsed;
    bool ok = qi::phrase_parse(f, l, parser, qi::space, parsed);

    if (ok)
    {
        std::cout << "Parse success\n";
    }
    else
    {
        std::cout << "Parse failed\n";
    }

    if (f!=l)
        std::cout << "Remaining unparsed input: '" << std::string(f,l) << "'\n";
}
