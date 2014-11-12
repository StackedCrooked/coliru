#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <string>

namespace qi = boost::spirit::qi;
namespace spirit = boost::spirit;
namespace ascii = boost::spirit::ascii;
using boost::phoenix::ref;

template <typename Iterator>
struct x_grammar : public qi::grammar<Iterator, ascii::space_type>
{   
public:
    x_grammar() : x_grammar::base_type(start_rule, "x_grammar")
    {   
        using namespace qi; 
        int repeat_count = 0;
        start_rule = int_[ref(repeat_count) = _1] > repeater > *char_;
        std::cout << "repeat_count == " << repeat_count << std::endl;
        repeater = repeat(ref(repeat_count))[int_[std::cout << _1 << ".\n"]];
    }   
private:
    qi::rule<Iterator, ascii::space_type> start_rule;
    qi::rule<Iterator, ascii::space_type> repeater;
};  

int main()
{   
    typedef std::string::const_iterator iter;
    std::string storage("5 1 2 3 4 5 garbage");
    iter it_begin(storage.begin());
    iter it_end(storage.end());
    using boost::spirit::ascii::space;
    x_grammar<iter> g;
    try {
        bool r = qi::phrase_parse(it_begin, it_end, g, space);
        if(r) {
            std::cout << "Pass!\n";
        } else {
            std::cout << "Fail!\n";
        }   
    } catch (const qi::expectation_failure<iter>& x) {
        std::cout << "Fail!\n";
    }   
}   