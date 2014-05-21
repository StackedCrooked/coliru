#include <boost/iostreams/device/mapped_file.hpp>
#include <boost/utility/string_ref.hpp>      // for zero-copy string
#include <boost/spirit/include/qi.hpp>       // for easy parsing
#include <boost/spirit/include/phoenix.hpp>  // for semantic action (constructing the field)
#include <iostream>

using CsvField = boost::string_ref;
using CsvLine  = std::vector<CsvField>;
using CsvFile  = std::vector<CsvLine>;

namespace qi = boost::spirit::qi;
struct CsvParser : qi::grammar<char const*, CsvFile()> {
    CsvParser() : CsvParser::base_type(lines)
    {
        using boost::phoenix::construct;
        using boost::phoenix::begin;
        using boost::phoenix::size;

        using namespace qi;

        field = raw [*~char_(",\r\n")] [ _val = construct<CsvField>(begin(_1), size(_1)) ];
        line  = field % ',';
        lines = line  % eol;
    }
  private:
    qi::rule<char const*, CsvField()> field;
    qi::rule<char const*, CsvLine()>  line;
    qi::rule<char const*, CsvFile()>  lines;
};

int main()
{
    srand(time(0));
    boost::iostreams::mapped_file_source csv("csv.txt");

    CsvFile parsed;
    parsed.reserve(3*1000*1000);
    if (qi::parse(csv.data(), csv.data() + csv.size(), CsvParser(), parsed))
    {
        std::cout << (csv.size() >> 20) << " MiB parsed into " << parsed.size() << " lines of CSV field values\n";

        for (int i = 0; i < 10; ++i)
        {
            auto l     = rand()%parsed.size();
            auto& line = parsed[l];
            auto c     = rand()%line.size();

            std::cout << "Random field at L:" << l << "\t C:" << c << "\t" << line[c] << "\n";
        }
    }
}
