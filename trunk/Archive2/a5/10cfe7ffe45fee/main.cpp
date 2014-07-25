#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace qi    = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace phx   = boost::phoenix;

struct ConditionTree {
    void AddDaysLimitOperator(unsigned) {}
    void AddHoursLimitOperator(unsigned) {}
    void AddMinutesLimitOperator(unsigned) {}
};

template <typename Iterator = std::string::const_iterator, typename Skipper = ascii::space_type>
struct Parser: qi::grammar<Iterator, ascii::space_type>
{
public:
  Parser(ConditionTree& a_lTree):
    Parser::base_type(limit_expression),
    m_lTree(a_lTree)
  {
    limit_expression = limit_days_operator | limit_hours_operator | limit_minutes_operator ;

    limit_days_operator    = ( "limit" >> qi::uint_ >> "days")   [ phx::bind( &ConditionTree::AddDaysLimitOperator,    phx::ref(m_lTree), qi::_1) ];
    limit_hours_operator   = ( "limit" >> qi::uint_ >> "hours")  [ phx::bind( &ConditionTree::AddHoursLimitOperator,   phx::ref(m_lTree), qi::_1) ];
    limit_minutes_operator = ( "limit" >> qi::uint_ >> "minutes")[ phx::bind( &ConditionTree::AddMinutesLimitOperator, phx::ref(m_lTree), qi::_1) ];

    BOOST_SPIRIT_DEBUG_NODE(limit_expression);

    BOOST_SPIRIT_DEBUG_NODE(limit_days_operator);
    BOOST_SPIRIT_DEBUG_NODE(limit_hours_operator);
    BOOST_SPIRIT_DEBUG_NODE(limit_minutes_operator);
  }

  qi::rule<Iterator, Skipper> limit_expression;
  qi::rule<Iterator, Skipper> limit_days_operator;
  qi::rule<Iterator, Skipper> limit_hours_operator;
  qi::rule<Iterator, Skipper> limit_minutes_operator;

  ConditionTree& m_lTree;
};

int main()
{
    ConditionTree oTree;

    Parser<> parser(oTree);

    std::string strTest("limit5minutes");

    std::string::const_iterator it_begin(strTest.begin());
    std::string::const_iterator it_end(strTest.end());

    bool result = phrase_parse(it_begin, it_end, parser, ascii::space);
}
