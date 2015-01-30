#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/optional/optional_io.hpp>

struct X {
    boost::optional<int> value1;
    boost::optional<int> value2;
    boost::optional<int> value3;
    boost::optional<int> value4;

};

static bool is_valid(X const& x) { return x.value1 && x.value2 && x.value4; } // value3 is optional

BOOST_FUSION_ADAPT_STRUCT(X,
        (boost::optional<int>, value1)
        (boost::optional<int>, value2)
        (boost::optional<int>, value3)
        (boost::optional<int>, value4)
    )

int main() {
    namespace qi = boost::spirit::qi;
    namespace phx = boost::phoenix;
    using It = std::string::const_iterator;

    qi::rule<It, X(), qi::space_type> grammar;
    grammar %=
        (("value1" > qi::lit('=') > qi::int_) ^
         ("value2" > qi::lit('=') > qi::int_) ^
         ("value3" > qi::lit('=') > qi::int_) ^
         ("value4" > qi::lit('=') > qi::int_))
        >> qi::eoi [ qi::_pass = phx::bind(is_valid, qi::_val) ]
        ;

    for (std::string const& input : {
            "value1 = 10\nvalue2 = 20\nvalue3 = 30\nvalue4 = 40\n",
            // Order doesn't matter but each value1 ... value4 line must be present exactly once. This would be OK:
            "value1 = 10\nvalue4 = 40\nvalue2 = 20\nvalue3 = 30\n",
            // But this would not be OK (duplicated value1):
            "value1 = 10\nvalue2 = 20\nvalue3 = 30\nvalue4 = 40\nvalue1 = 10000\n",
            // Nor this (missing value4):
            "value1 = 10\nvalue2 = 20\nvalue3 = 30\n",
            // value3 _is_ optional though:
            "value1 = 10\nvalue2 = 20\nvalue4 = 40\n",
        })
    {
        std::cout << "---------------------------------------------------------\n";
        std::cout << "Parsing '" << input << "'\n";
        auto f(input.begin()), l(input.end());
        X parsed;
        bool ok = phrase_parse(f, l, grammar, qi::space, parsed);

        if (ok) {
            std::cout << "Parsing succeeded: " << boost::fusion::as_vector(parsed) << "\n";
        } else {
            std::cout << "Parsing failed\n";
        }

        if (f!=l)
            std::cout << "Remaing input '" << std::string(f,l) << "'\n";
    }
}
