#include <boost/spirit/include/qi.hpp>
namespace qi = boost::spirit::qi;

int main()
{
    std::vector<std::string> testVec;
    testVec.push_back("25.16");
    testVec.push_back("2516");
    std::string result;
    std::string::const_iterator it, endIt;

    for (unsigned int i = 0; i < testVec.size(); ++i)
    {
        it = testVec[i].begin();
        endIt = testVec[i].end();
        result.clear();

        std::cout << "test" << i << "a: ";
        bool r = qi::phrase_parse(
            it,
            endIt,
            +qi::digit >> -(qi::string(".") >> +qi::digit),
            qi::space,
            result
        );

        if (!r || it != endIt)
        {
            std::cout << "failed" << std::endl;
        }
        else
        {
            std::cout << result << std::endl;
        }

        it = testVec[i].begin();
        endIt = testVec[i].end();
        result.clear();

        std::cout << "test" << i << "b: ";
        r = qi::phrase_parse(
            it,
            endIt,
            +qi::digit >> (qi::string(".") >> +qi::digit),
            qi::space,
            result
        );

        if (!r || it != endIt)
        {
            std::cout << "failed" << std::endl;
        }
        else
        {
            std::cout << result << std::endl;
        }
    }

    return 0;
}