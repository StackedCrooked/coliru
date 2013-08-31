//#define BOOST_SPIRIT_DEBUG
#include <boost/spirit/include/qi.hpp>

namespace qi = boost::spirit::qi;

using Column  = std::string;
using Columns = std::vector<Column>;
using CsvLine = Columns;
using CsvFile = std::vector<CsvLine>;

template <typename It>
struct CsvGrammar : qi::grammar<It, CsvFile(), qi::blank_type>
{
    CsvGrammar() : CsvGrammar::base_type(start)
    {
        using namespace qi;

        static const char colsep = ',';

        start  = -line % eol;
        line   = column % colsep;
        column = quoted | *~char_(colsep);
        quoted = '"' >> *("\"\"" | ~char_('"')) >> '"';

        BOOST_SPIRIT_DEBUG_NODES((start)(line)(column)(quoted));
    }
  private:
    qi::rule<It, CsvFile(), qi::blank_type> start;
    qi::rule<It, CsvLine(), qi::blank_type> line;
    qi::rule<It, Column(),  qi::blank_type> column;
    qi::rule<It, std::string()> quoted;
};

int main()
{
    const std::string s = R"(1997,Ford,E350,"ac, abs, moon","""rusty""",3001.00)";

    auto f(begin(s)), l(end(s));
    CsvGrammar<std::string::const_iterator> p;

    CsvFile parsed;
    bool ok = qi::phrase_parse(f,l,p,qi::blank,parsed);

    if (ok)
    {
        for(auto& line : parsed) {
            for(auto& col : line)
                std::cout << '[' << col << ']';
            std::cout << std::endl;
        }
    } else
    {
        std::cout << "Parse failed\n";
    }

    if (f!=l)
        std::cout << "Remaining unparsed: '" << std::string(f,l) << "'\n";
}
