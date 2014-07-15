#include <boost/spirit/include/qi.hpp>
#include <boost/optional/optional_io.hpp>

namespace qi = boost::spirit::qi;

int main()
{
    auto test = [](std::string const input) {
        boost::optional<int> result;
        assert(qi::parse(input.begin(), input.end(), -qi::int_, result));
        return result;
    };

    std::cout << test("abc") << "\n"; 
    std::cout << test("123") << "\n"; 
}
