#include <boost/spirit/include/karma.hpp>

namespace karma = boost::spirit::karma;

typedef boost::variant<double, unsigned int, std::string> V;

struct gen : karma::grammar<boost::spirit::ostream_iterator, V()> {
    gen() : gen::base_type(start) 
    {
        using namespace karma;
        start = auto_;
    }
  private:
    karma::rule<boost::spirit::ostream_iterator, V()> start;
};

int main()
{
    for(auto v : { V{42u}, V{3.1416}, V{"Life Of Pi"} })
        std::cout << karma::format(gen(), v) << "\n";
}
