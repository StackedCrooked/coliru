#include <boost/spirit/include/qi.hpp> 
namespace qi = boost::spirit::qi;

typedef std::string::const_iterator It;
static const qi::rule<It, int()> number = 
           ("16#" >> qi::int_parser<int, 16, 1>())
         | ("2#"  >> qi::int_parser<int,  2, 1>())
         | ("8#"  >> qi::int_parser<int,  8, 1>())
         | qi::int_
       ;

int main() {
    for (std::string const input : { "17", "16#FF", "2#1001" }) {
        It f(input.begin()), l(input.end());

        int data;
        if(qi::parse(f, l, number, data))
             std::cout << "Parse success ('" << input << "': " << data << ")\n";
        else std::cout << "Parse failed ('" << input << "')\n";

        if (f != l)
            std::cout << "Input remaining: '" << std::string(f, l) << "'\n";
    }
}
