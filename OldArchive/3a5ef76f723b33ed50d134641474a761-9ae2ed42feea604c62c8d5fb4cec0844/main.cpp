#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

int main()
{
    typedef std::vector<std::vector<double>> data_t;
    typedef boost::spirit::istream_iterator It;

    std::cin.unsetf(std::ios::skipws);
    It first(std::cin), last;

    bool ok;
    data_t contents;

    {
        using namespace boost::spirit::qi;
        static rule<It, std::vector<std::vector<double>>(), blank_type, locals<int>> file;
        static rule<It, std::vector<double>(int number),    blank_type>              row;

        _a_type number; // friendly alias

        file %= -(omit [int_[number=_1]] > eol > row(number)) % eol;
        row   = repeat(_r1) [ double_ ];

        ok = phrase_parse(first, last, file, blank, contents);
    }

    if (ok) for (auto& row : contents)
    {
        std::copy(row.begin(), row.end(), std::ostream_iterator<double>(std::cout," "));
        std::cout << "\n";
    }

    if (first!=last)
        std::cout << "Warning: end of file not reached, remaining unparsed: '" << std::string(first, last) << "'\n";
}
