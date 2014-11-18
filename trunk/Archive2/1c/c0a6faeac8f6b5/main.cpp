#include <boost/spirit/include/karma.hpp>

namespace karma = boost::spirit::karma;

struct ceva{};

typedef boost::variant<double, unsigned int, ceva> V;

template <typename iterator>
struct gen : karma::grammar<iterator, V(), boost::spirit::ascii::space_type> {
    gen() : gen::base_type(start) 
    {
        using namespace karma;

        start %= karma::lit("mata") << (my_real | my_uint | karma::omit[my_ip]);

        my_uint = "The value is unsigned integral value (" << uint_ << ")";
        my_real = "The value is double precision floating point value (" << double_ << ")";
    }
  private:
    karma::rule<iterator, V(), boost::spirit::ascii::space_type>           start;
    karma::rule<iterator, double()>      my_real;
    karma::rule<iterator, unsigned       int()>   my_uint;
    karma::rule<iterator, ceva()> my_ip;
};

int main()
{
    ceva c;
    for(auto v : { V{42u}, V{3.1416}, V{c} }) {
        std::string output;
        std::back_insert_iterator<std::string> it(output);
        bool result = karma::generate_delimited(it, gen<decltype(it)>(), boost::spirit::ascii::space, v);
        std::cout << output << "\n";
        std::cout << result << "\n";
    }
}
