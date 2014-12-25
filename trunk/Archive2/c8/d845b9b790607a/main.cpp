#include <boost/spirit/include/qi.hpp>
#include <boost/proto/deep_copy.hpp>
#include <boost/optional.hpp>

#include <string>

namespace qi = boost::spirit::qi;

template <typename It/*, typename Skipper*/>
struct string_literal : qi::grammar<It, std::string()/*, Skipper*/> {
    string_literal() : string_literal::base_type(start) {
        start = '"'
             >> *(('\\' >> qi::char_) | (qi::char_ - '"'))
             >> '"'
             ;
    }
    qi::rule<It, std::string()/*, Skipper*/> start;
};

template <class Iterator, class Grammar>
boost::optional<std::string> parse_string(Iterator first, Iterator last, Grammar const& gr)
{
    std::string temp;

    bool success = qi::phrase_parse(
        first,
        last,
        gr,
        qi::space,
        temp
    );

    if (success && first == last)
        return temp;
    else return boost::none;
}


int main()
{
    std::string str;
    std::cout << "string_literal: ";

    getline(std::cin, str);

    auto presult = parse_string(str.cbegin(), str.cend(), string_literal<std::string::const_iterator>());
    if (presult) {
        std::cout << "parsed: '" << *presult << "'\n";
    } else
        std::cout << "failure\n";

    return 0;
}
