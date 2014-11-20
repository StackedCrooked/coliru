#include <boost/spirit/include/qi.hpp>

using It  = boost::spirit::istream_iterator;
using Row = std::vector<double>;
using Mat = std::vector<Row>;

int main() {
    It f(std::cin>>std::noskipws), l;

    Mat matrix;
    std::string name;

    {
        using namespace boost::spirit::qi;
        rule<It, std::string()> varname_ = char_("a-zA-Z_") >> *char_("a-zA-Z0-9_");

        if (phrase_parse(f, l, 
                lit("MATRIX") >> '.' >> '{' >> varname_ >> '}' >> '=' 
                    >> '[' >> (int_ % ',' % ';') >> ']',
                space, name, matrix))
        {
            std::cout << "Parsed: variabled named '" << name << "' [";

            for(auto& row : matrix)
                std::copy(row.begin(), row.end(), std::ostream_iterator<double>(std::cout<<"\n\t",", "));
            std::cout << "\n]\n";
        } else {
            std::cout << "Parse failed\n";
        }
    }

    if (f!=l)
        std::cout << "Remaining input: '" << std::string(f,l) << "'\n";
}
