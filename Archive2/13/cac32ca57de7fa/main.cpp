#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/version.hpp> 
#include <string>

namespace qi = boost::spirit::qi;
namespace spirit = boost::spirit;
namespace ascii = boost::spirit::ascii;
using boost::phoenix::ref;
using boost::phoenix::bind;

void dummy(const std::vector<char>& v, int& var)
{
    std::cout << "var (" << &var << ") was " << var;
    var = 7;
    std::cout << " and now it is " << var << std::endl;;
}

template <typename Iterator>
struct x_grammar : public qi::grammar<Iterator, std::string(), ascii::space_type>
{
public:
    x_grammar() : x_grammar::base_type(start_rule, "x_grammar")
    {
        using namespace qi;
        static int local_var = 0;
        std::cout << "var is at " << &local_var << std::endl;
        start_rule = (+(char_ - ";"))[bind(dummy, _1, ref(local_var))];
        //repeat(ref(local_var))[some_rule];
    }
private:
    qi::rule<Iterator, std::string(), ascii::space_type> start_rule;
};

int main()
{
    std::cout << BOOST_LIB_VERSION << std::endl;
    typedef std::string::const_iterator iter;
    std::string storage("string;aaa");
    iter it_begin(storage.begin());
    iter it_end(storage.end());
    std::string read_data;
    using boost::spirit::ascii::space;
    x_grammar<iter> g;
    try {
        bool r = qi::phrase_parse(it_begin, it_end, g, space, read_data);
        std::cout << "Pass!\n";
    } catch (const qi::expectation_failure<iter>& x) {
        std::cout << "Error!\n";
    }
}