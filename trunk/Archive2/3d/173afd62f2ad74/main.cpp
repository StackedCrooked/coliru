#include <boost/spirit/include/qi.hpp>
namespace qi = boost::spirit::qi;

void test(std::string const& input)
{
    std::string result;
    std::string::const_iterator 
        it    = input.begin(),
        endIt = input.end();

    bool r = qi::phrase_parse(
        it, endIt,
        qi::raw [ qi::lexeme [ +qi::digit >> -('.' >> +qi::digit) ] ],
        qi::space, result
    );

    if (!r || it != endIt)
        std::cout << "failed" << std::endl;
    else
        std::cout << result << std::endl;
}

int main()
{
    test("25.16");
    test("2516");
}
