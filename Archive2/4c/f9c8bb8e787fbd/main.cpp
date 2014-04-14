#include <boost/spirit/include/qi.hpp>
namespace qi = boost::spirit::qi;

int main()
{
    std::string const tests[] = {
        "SomeString #222",
        "SomeString #1",
        "SomeString #42",
        "SomeString #-1"
    };

    for(auto& input : tests)
    {
        int value;
        auto f(input.begin()), l(input.end());
        if (qi::phrase_parse(f, l,  // input iterators
                    qi::omit [ *~qi::char_('#') ] >> '#' >> qi::int_, // grammar
                    qi::space,      // skipper
                    value))         // output attribute
        {
            std::cout << "     Input '" << input << "' -> " << value << "\n";
        }
    }
}
