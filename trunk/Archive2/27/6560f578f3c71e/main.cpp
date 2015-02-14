#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

struct Aha {
    std::string erlebnis;
    int some_value;
};

namespace qi = boost::spirit::qi;

namespace parser {
    namespace px = boost::phoenix;
    using     It = std::string::const_iterator;

    static const auto erlebnis_   = px::bind(&Aha::erlebnis,   qi::_val);
    static const auto some_value_ = px::bind(&Aha::some_value, qi::_val);

    static qi::rule<It, Aha(), qi::space_type> rule =
          qi::double_                                 [ some_value_ = 100.0 * qi::_1 ]
                                                      [ qi::_pass = (some_value_ <= 100) && (some_value_ >= 0) ] 
        > ';' 
        > qi::as_string [ qi::lexeme [ +qi::graph ] ] [ erlebnis_ = qi::_1 ]
        ;
}
    
int main() {
    using parser::rule;

    for (std::string const test : {
            ".42; some_word",
            "  16e-02    \n; yup   ",
            "-inf; some_word",
            })
    {
        auto f(begin(test)), l(end(test));
        Aha data;
        if (qi::phrase_parse(f, l, parser::rule, qi::space, data))
            std::cout << "Parsed: (" << data.some_value << ", '" << data.erlebnis << "')\n";
        else
            std::cout << "Parse failed\n";

        if (f!=l)
            std::cout << "Remaining unparsed: '" << std::string(f,l) << "'\n";
    }
}
