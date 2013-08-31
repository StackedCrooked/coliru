#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace qi    = boost::spirit::qi;

struct X
{
    typedef void result_type;

    template <typename T>
    void operator()(T const&) const { std::cout << typeid(T).name() << "\n"; }
};

int main()
{
    const std::string x = "1,2,3;2,3,4;3,4,5";

    auto f(begin(x)), l(end(x));
    qi::rule<std::string::const_iterator, std::vector<short>()> input = qi::short_ % ',';
    qi::parse(f, l, 
            (input >> (qi::repeat(0,2)[qi::char_(';') >> input])) [ X() ]);
}
