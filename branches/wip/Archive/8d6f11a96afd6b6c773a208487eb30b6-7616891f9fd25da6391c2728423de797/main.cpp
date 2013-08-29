#define BOOST_SPIRIT_DEBUG
#include <boost/fusion/adapted.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace qi = boost::spirit::qi;
namespace phx = boost::phoenix;

struct rowType {
    unsigned int number;
    std::list<unsigned int> list;
};

struct problemType {
    unsigned int ROW;
    std::vector<rowType> rows;
};

BOOST_FUSION_ADAPT_STRUCT(rowType, (unsigned int, number)(std::list<unsigned int>, list))
BOOST_FUSION_ADAPT_STRUCT(problemType, (unsigned int, ROW)(std::vector<rowType>, rows))

template<typename Iterator>
struct problem_parser : qi::grammar<Iterator,problemType(),qi::blank_type>
{
    problem_parser() : problem_parser::base_type(problem)
    {
        using namespace qi;
        list    = '[' >> -(int_ % ',') >> ']';
        row     = int_ >> list >> eol;
        problem = "ROW" >> int_ >> eol >> +row;

        BOOST_SPIRIT_DEBUG_NODES((problem)(row)(list));
    }

    qi::rule<Iterator, problemType()            , qi::blank_type> problem;
    qi::rule<Iterator, rowType()                , qi::blank_type> row;
    qi::rule<Iterator, std::list<unsigned int>(), qi::blank_type> list;
};

int main()
{
    const std::string input = 
        "ROW 1\n"
        "2 [3, 4]\n"
        "5 [6, 7]\n";

    auto f = begin(input), l = end(input);

    problem_parser<std::string::const_iterator> p;
    problemType data;

    bool ok = qi::phrase_parse(f, l, p, qi::blank, data);

    if (ok) std::cout << "success\n";
    else    std::cout << "failed\n";

    if (f!=l)
        std::cout << "Remaining unparsed: '" << std::string(f,l) << "'\n";
}
