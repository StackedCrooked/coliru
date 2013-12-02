#include <boost/spirit/include/qi.hpp>

int main()
{
    std::string const s = "hello\r\nworld";

    std::vector<std::string> lines;

    {
        using namespace boost::spirit::qi;
        auto f(std::begin(s)), l(std::end(s));
        /*bool ok =*/ parse(f, l, *(char_-eol) % eol, lines);
    }

    for (auto const& range : lines)
    {
        std::cout << "'" << range  << "'\n";
    };
}
