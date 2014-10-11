#include <boost/spirit/include/karma.hpp>

namespace karma = boost::spirit::karma;

typedef boost::variant<double, unsigned int, std::string> V;

struct gen : karma::grammar<boost::spirit::ostream_iterator, V()> {
    gen() : gen::base_type(start) 
    {
        using namespace karma;

        start = my_real | my_uint | my_text;

        my_uint = "The value is unsigned integral value (" << uint_ << ")";
        my_real = "The value is double precision floating point value (" << double_ << ")";
        my_text = "The value is an epos: '" << *quoted_char << "'";

        quoted_char = '\\' << char_("'") | graph | "\\x" << uint_generator<uint8_t, 16>();
    }
  private:
    karma::rule<boost::spirit::ostream_iterator, V()>           start;
    karma::rule<boost::spirit::ostream_iterator, double()>      my_real;
    karma::rule<boost::spirit::ostream_iterator, unsigned       int()>   my_uint;
    karma::rule<boost::spirit::ostream_iterator, std::string()> my_text;
    karma::rule<boost::spirit::ostream_iterator, uint8_t()>     quoted_char;
};

int main() {
    std::cout << karma::format(gen() % ";\n", std::vector<V>{42u,3.1416,"It's a beautiful day!"}) << "\n";
}
