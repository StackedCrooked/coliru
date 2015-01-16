//#define BOOST_SPIRIT_DEBUG
#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <iostream>
#include <boost/fusion/include/at_c.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <string>
#include <vector>

namespace qi = boost::spirit::qi;
namespace phx = boost::phoenix;

using std::string;

enum LineItems { NAME, AGE, UNUSED };

struct CsvLine {
    string name;
    int age;
};

using Column  = std::string;
using Columns = std::vector<Column>;
using CsvFile = std::vector<CsvLine>;

template<typename It>
struct CsvGrammar: qi::grammar<It, CsvFile(), qi::locals<std::vector<LineItems>>, qi::blank_type> {
    CsvGrammar() : CsvGrammar::base_type(start) {
        using namespace qi;
        static const char colsep = ',';

        item.add("Name", NAME)("Age", AGE);
        start  = qi::omit[ header[_a=_1] ] >> eol >> line(_a) % eol;

        header = (item | omit[column] >> attr(UNUSED)) % colsep;
        line   = (column % colsep) [convert];

        column = quoted | *~char_(",\n");
        quoted = '"' >> *("\"\"" | ~char_("\"\n")) >> '"';

        BOOST_SPIRIT_DEBUG_NODES((header)(column)(quoted));
    }

private:
    qi::rule<It, std::vector<LineItems>(),                      qi::blank_type> header;
    qi::rule<It, CsvFile(), qi::locals<std::vector<LineItems>>, qi::blank_type> start;
    qi::rule<It, CsvLine(std::vector<LineItems> const&),        qi::blank_type> line;

    qi::rule<It, Column(), qi::blank_type> column;
    qi::rule<It, std::string()> quoted;
    qi::rule<It, qi::blank_type> empty;

    qi::symbols<char, LineItems> item;

    struct final {
        using Ctx = typename decltype(line)::context_type;

        void operator()(Columns const& columns, Ctx &ctx, bool &pass) const {
            auto& csvLine   = boost::fusion::at_c<0>(ctx.attributes);
            auto& positions = boost::fusion::at_c<1>(ctx.attributes);
            int i =0;

            for (LineItems position : positions) {
                switch (position) {
                    case NAME: csvLine.name = columns[i];              break;
                    case AGE:  csvLine.age = atoi(columns[i].c_str()); break;
                    default:   break;
                }
                i++;
            }

            pass = true; // returning false fails the `line` rule
        }
    } convert;
};

int main() {
    const std::string s = "Surname,Name,Age,\nJohn,Doe,32\nMark,Smith,43";

    auto f(begin(s)), l(end(s));
    CsvGrammar<std::string::const_iterator> p;

    CsvFile parsed;
    bool ok = qi::phrase_parse(f, l, p, qi::blank, parsed);

    if (ok) {
        for (CsvLine line : parsed) {
            std::cout << '[' << line.name << ']' << '[' << line.age << ']';
            std::cout << std::endl;
        }
    } else {
        std::cout << "Parse failed\n";
    }

    if (f != l)
        std::cout << "Remaining unparsed: '" << std::string(f, l) << "'\n";
}
