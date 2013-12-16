#define BOOST_SPIRIT_DEBUG

#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/container/vector.hpp>

namespace karma = boost::spirit::karma;

int main()
{
    boost::variant<boost::container::vector<int>, std::string> tmp = "test";
    std::string use;
    bool r = karma::generate(std::back_inserter(use), +karma::int_ | karma::string, tmp);

    std::cout << std::boolalpha << r << "\t" << use << "\n";
}
