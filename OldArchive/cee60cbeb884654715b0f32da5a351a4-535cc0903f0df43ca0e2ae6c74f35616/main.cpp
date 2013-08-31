#include <boost/variant.hpp>
#include <boost/spirit/include/karma.hpp>

namespace karma = boost::spirit::karma;
typedef boost::make_recursive_variant<int, std::string, std::vector<boost::recursive_variant_> >::type Parameter;
typedef std::vector<Parameter> Parameters;

int main()
{
    typedef boost::spirit::ostream_iterator It;

    karma::rule<It, Parameter()>   gen;
    karma::rule<It, std::string()> str;

    str = '"' << *('\\' << karma::char_('"') | karma::char_) << '"';
    gen = (karma::int_ | str | '{' << gen % ", " << '}');

    for (Parameter p : Parameters { 
            1, 
            "foo",
            Parameters { 1, "foo" },
            Parameters { 1, "escape: \"foo\"", Parameters { "2", "bar" } } 
       })
    {
        std::cout << karma::format(gen, p) << '\n';
    }
}
