#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/spirit/include/qi.hpp>
#include <map>

typedef boost::variant<double, std::string> Value;
typedef std::map<std::string, Value>        AST;

int main() {
    namespace qi = boost::spirit::qi;
    typedef boost::spirit::istream_iterator It;
    static qi::rule<It, std::string()> const string_ = +~qi::char_("[]\r\n");

    It begin(std::cin >> std::noskipws), end;

    AST ast;
    bool success = qi::phrase_parse(begin, end, 
            ('[' >> string_ >> ']' >> (qi::double_|string_)) % qi::eol,
            qi::blank, ast);

    if (success) for (auto& e : ast) 
        std::cout << '[' << e.first << "]\t" << e.second << "\n";
}
