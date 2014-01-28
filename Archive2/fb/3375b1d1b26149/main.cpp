#include <boost/fusion/adapted.hpp>
#include <boost/spirit/home/qi.hpp>

namespace qi = boost::spirit::qi;

namespace boost { namespace spirit { namespace traits {   
    // be careful copying expression templates. Boost trunk has `qi::copy` for this too, now
    #define PARSER_DEF(a) using type = decltype(boost::proto::deep_copy(a)); static type call() { return boost::proto::deep_copy(a); }

    template<typename T1, typename T2> 
        struct create_parser<std::pair<T1, T2> > 
        {
            PARSER_DEF(lexeme [ lit("PAIR") ] >> '(' >> create_parser<T1>::call() >> ',' >> create_parser<T2>::call() >> ')');
        };

    template<typename TV, typename... TArgs>
        struct create_parser<std::vector<TV, TArgs...> >
        {
            PARSER_DEF(lexeme [ lit("VECTOR") ] >> '[' >> qi::omit[qi::uint_] >> ',' >> '(' >> create_parser<TV>::call() % ',' >> ')' >> ']' );
        };

    #undef PARSER_DEF
} } }

#include <boost/spirit/home/karma.hpp>
namespace karma = boost::spirit::karma;

int main()
{
    std::string const input("VECTOR[ 1 ,\n"
                " (               \n"
                "     PAIR (0.97, \n"
                "           5),   \n"
                "     PAIR (1.75,10)   \n"
                " )               \n"
            "]");

    std::cout << input << "\n\n";

    auto first = input.begin();
    auto last = input.end();

    std::vector<std::pair<double, int> > parsed;
    bool result_ = qi::phrase_parse(first, last, qi::auto_, qi::space, parsed);

    if (first!=last)
        std::cout << "Remaining unparsed input: '" << std::string(first, last) << "'\n";

    if (result_)
        std::cout << "Parsed:\n " << karma::format_delimited(karma::auto_ % karma::eol, " ", parsed) << "\n";
    else
        std::cout << "Parsing did not succeed\n";
}

