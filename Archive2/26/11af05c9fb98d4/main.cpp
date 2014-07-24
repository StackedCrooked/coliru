#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace qi    = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace phx   = boost::phoenix;

struct ConditionTree {
    struct Limit {
        unsigned value;
        enum unit_t { days, hours, minutes } unit;
    };

    friend void AddLimit(ConditionTree& ct, Limit limit) {
        std::cout << __PRETTY_FUNCTION__ << ": " << limit.value;
        switch (limit.unit) {
            case Limit::days:    std::cout << " days\n"; break;
            case Limit::hours:   std::cout << " hours\n"; break;
            case Limit::minutes: std::cout << " minutes\n"; break;
        }
    }
};

BOOST_FUSION_ADAPT_STRUCT(ConditionTree::Limit, (unsigned,value)(ConditionTree::Limit::unit_t,unit))

template <typename Iterator = std::string::const_iterator, typename Skipper = ascii::space_type>
struct Parser: qi::grammar<Iterator, ConditionTree::Limit(), ascii::space_type>
{
    public:
        Parser() : Parser::base_type(limit_expression)
    {
        unit_.add("days",    ConditionTree::Limit::days)
                 ("hours",   ConditionTree::Limit::hours)
                 ("minutes", ConditionTree::Limit::minutes);

        limit_expression = "limit" >> qi::uint_ >> unit_;
    }

    qi::symbols<char, ConditionTree::Limit::unit_t> unit_;
    qi::rule<Iterator, ConditionTree::Limit(), Skipper> limit_expression;
};

int main()
{
    ConditionTree oTree;

    Parser<> parser;

    std::string strTest("limit5minutes");

    std::string::const_iterator iter(strTest.begin()), end(strTest.end());

    ConditionTree::Limit limit;
    if (phrase_parse(iter, end, parser, ascii::space, limit))
    {
        AddLimit(oTree, limit);
    }
}
