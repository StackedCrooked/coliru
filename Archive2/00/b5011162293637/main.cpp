#include <boost/spirit/include/qi.hpp>
namespace qi = boost::spirit::qi;

int main() {
    std::string const sentence = "My dog Fluffy\\ Cake likes to jump";
    using It = std::string::const_iterator;
    It f = sentence.begin(), l = sentence.end();

    std::vector<std::string> words;

    bool ok = qi::phrase_parse(f, l,
            *qi::lexeme [ +('\\' >> qi::char_ | qi::graph) ], // words
            qi::space - "\\ ", // skipper
            words);

    if (ok) {
        std::cout << "Parsed:\n";
        for (auto& w : words)
            std::cout << "\t'" << w << "'\n";
    } else {
        std::cout << "Parse failed\n";
    }

    if (f != l)
        std::cout << "Remaining unparsed: '" << std::string(f,l) << "'\n";
}
