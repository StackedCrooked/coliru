#include <boost/spirit/include/qi.hpp>
#include <boost/proto/deep_copy.hpp>
#include <boost/optional.hpp>

#include <string>

namespace qi = boost::spirit::qi;

namespace {

    auto string_literal = boost::proto::deep_copy(
#if 1
        qi::lexeme [
                '"' >>
                    *(('\\' >> qi::char_) | (qi::char_ - '"'))
                >> '"'
            ]
#else
        qi::raw [
                '"' >>
                    *(('\\' >> qi::char_) | (qi::char_ - '"'))
                >> '"'
            ]
#endif
        );

}

template <class Iterator, class Grammar>
boost::optional<std::string> parse_string(Iterator first, Iterator last, Grammar&& gr)
{
    std::string temp;

    bool success = qi::phrase_parse(
        first,
        last,
        std::forward<Grammar>(gr),
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

    auto presult = parse_string(str.begin(), str.end(), string_literal);
    if (presult) {
        std::cout << "parsed: '" << *presult << "'\n";
    } else
        std::cout << "failure\n";

    return 0;
}
