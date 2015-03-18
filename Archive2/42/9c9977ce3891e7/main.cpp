#include <boost/spirit/include/qi.hpp>

namespace qi = boost::spirit::qi;

struct tokens : qi::symbols<char, int>
{
    tokens() {
        add
            ("This",  10)
            ("is",    73)
            ("the",   5)
            ("input", 32);
    }
};

int main() {
    std::string const input("This is the input");

    std::vector<int> parsed;
    std::string::const_iterator f = input.begin(), l = input.end();
    bool ok = qi::phrase_parse(f, l, +tokens(), qi::space, parsed);

    if (ok)
        std::cout << "Parse success: ";
    else
        std::cout << "Parse failed: ";

    std::copy(parsed.begin(), parsed.end(), std::ostream_iterator<int>(std::cout, " "));

    if (f!=l)
        std::cout << "\nRemaining input: '" << std::string(f,l) << "'\n";
}
