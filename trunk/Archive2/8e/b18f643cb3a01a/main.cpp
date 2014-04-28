#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/include/qi.hpp>

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

struct LineOnCommand
{
   int lineNum;
   std::vector<char> humpType;
};

BOOST_FUSION_ADAPT_STRUCT(
   LineOnCommand,
   (int, lineNum)
   (std::vector<char>, humpType)
)

template <typename It, typename Skipper = ascii::space_type>
struct parser : qi::grammar<It, std::vector<LineOnCommand>(), Skipper>
{
    parser() : parser::base_type(commands)
    {
        using namespace qi;
        humpIdentifier = lit("BH") | "DH";
        Cmd_LNON       = int_ >> -humpIdentifier >> "LNON";

        commands       = +( /* other rules | */ Cmd_LNON /*| other rules */ );
    }
  private:
    qi::rule<It, std::vector<char>(),          Skipper> humpIdentifier;
    qi::rule<It, LineOnCommand(),              Skipper> Cmd_LNON;
    qi::rule<It, std::vector<LineOnCommand>(), Skipper> commands;
};

int main()
{
    typedef std::string::const_iterator Iterator;
    parser<Iterator> p;

    std::string const input = 
        "123 BH LNON\n"
        "124 LNON\t\t\t"
        "125 DH LNON\n"
        "126 INVALID LNON";

    auto f(input.begin()), l(input.end());

    std::vector<LineOnCommand> data;
    bool success = qi::phrase_parse(f, l, p, ascii::space, data);

    std::cout << "success:" << std::boolalpha << success << ", " 
              << "elements: " << data.size() << "\n";

    if (f!=l)
        std::cout << "Trailing unparsed: '" << std::string(f,l) << "'\n";

    return success? 0 : 1;
}
