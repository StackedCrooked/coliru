#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <fstream>
#include <map>

namespace /*parser*/ 
{
    namespace qi  = boost::spirit::qi;
    using It      = boost::spirit::istream_iterator; 
    using Value   = double; // int, if you prefer
    using Result  = std::pair<int, Value>;
    using Results = std::map <int, Value>;

    template <typename Sig>
        using Rule = qi::rule<It, Sig, qi::space_type>;

    using namespace boost::spirit::qi;

    static const lexeme_type L;

    Rule<Value(std::string /*element_name*/)> 
        value_     = eps >> '<' >> L[lit(_r1)] > '>' > auto_ > '<' > '/' > L[lit(_r1)] > '>',
        expr_open  = eps >> '<' >> L[lit(_r1)] > L["id"] > '=' > '"' > auto_ > '"' > '>';
    Rule<void(std::string /*element_name*/)> 
        expr_close = eps >> '<' >> '/' > L[lit(_r1)] > '>';

    // evaluation on the fly
    Rule<Value()> 
        addition_r       = +value_(+"item")                             [ _val += _1      ],
        subtraction_r    = (value_(+"minuend") > value_(+"subtrahend")) [ _val  = _1 - _2 ],
        multiplication_r = eps [ _val = 1 ] >> +value_(+"factor")       [ _val *= _1      ],
        division_r       = (value_(+"dividend") > value_(+"divisor"))   [ _val  = _1 / _2 ];

    // expression element parsing
    Rule<Result()> 
        addition_       = expr_open(+"addition")       > addition_r       > expr_close(+"addition"),
        subtraction_    = expr_open(+"subtraction")    > subtraction_r    > expr_close(+"subtraction"),
        multiplication_ = expr_open(+"multiplication") > multiplication_r > expr_close(+"multiplication"),
        division_       = expr_open(+"division")       > division_r       > expr_close(+"division");

} /*parser*/

int main()
{
    std::ifstream ifs("expressions.xml");
    It f(ifs >> std::noskipws), l;

    try {
        Results results;

        // parsing
        bool ok = phrase_parse(f, l, eps
                > '<' > L["expressions"] > '>'
                > *(addition_|subtraction_|multiplication_|division_)
                > expr_close(+"expressions"),
                space, results);

        // output results
        if (ok)
        {
            std::cout << "<expressions>\n";
            for (auto& result : results)
            {
                std::cout << "\t<result id=\"" << result.first << "\">" << result.second << "</result>\n";
            }
            std::cout << "</expressions>\n";
        }
    } catch(expectation_failure<It> const& e) {
        std::cout << "Expected " << e.what_ << " at '" << std::string(e.first,e.last) << "'\n";
    }
}
