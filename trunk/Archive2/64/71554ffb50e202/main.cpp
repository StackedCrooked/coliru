#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_match.hpp>

int main() {
    std::vector<std::string> three_wordses;
    {
        using namespace boost::spirit::qi;

        rule<boost::spirit::istream_iterator, std::string()> wordses =
            repeat(1,3)[+graph >> *(*omit[eol] >> space)];

        std::cin >> std::noskipws >> phrase_match(+wordses, space, three_wordses);
        std::cout << "three_wordses: " << three_wordses.size() << "\n";
    }

    for(auto s : three_wordses)
        std::cout << "'" << s << "'\n";
}
