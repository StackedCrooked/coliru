//#define BOOST_SPIRIT_DEBUG
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/phoenix.hpp>

#include <boost/fusion/adapted.hpp>
#include <iostream>
#include <fstream>

struct c_struct {
    int value1;
};

struct b_struct {
    std::string value1;
    std::vector<c_struct> value2;
};

struct a_struct {
    std::string value1;
    std::vector<b_struct> value2;
};

BOOST_FUSION_ADAPT_STRUCT(c_struct, (int, value1))
BOOST_FUSION_ADAPT_STRUCT(b_struct, (std::string, value1)(std::vector<c_struct>, value2))
BOOST_FUSION_ADAPT_STRUCT(a_struct, (std::string, value1)(std::vector<b_struct>, value2))

namespace qi    = boost::spirit::qi;
namespace karma = boost::spirit::karma;
namespace ascii = boost::spirit::ascii;

template <typename Iterator> struct grammarB : karma::grammar<Iterator, a_struct(), karma::space_type> {
    grammarB() : grammarB::base_type(start) {
        using namespace karma;
        _a_type _pass_along;
        _r1_type _inherited;

        start = ruleA;
        
        ruleA %= string [ _pass_along = _1 ] << +ruleB(_pass_along);
        //ruleB  = string << +ruleC(_inherited);
        ruleB  = lit(_inherited) << string << +ruleC(_inherited); // alternative interpretation
        ruleC  = "->" << lit(_inherited) << karma::int_;

        BOOST_SPIRIT_DEBUG_NODES((start)(ruleA)(ruleB)(ruleC))
    }

    karma::rule<Iterator, a_struct(), karma::space_type> start;
    karma::rule<Iterator, a_struct(), qi::locals<std::string>, karma::space_type> ruleA;
    karma::rule<Iterator, b_struct(std::string const&), karma::space_type> ruleB;
    karma::rule<Iterator, c_struct(std::string const&), karma::space_type> ruleC;
};

template <typename Iterator> struct grammarA : qi::grammar<Iterator, a_struct(), boost::spirit::ascii::space_type> {
    grammarA() : grammarA::base_type(ruleA) {
        using namespace qi;
        ruleA = ruleString >> lexeme[+qi::lit('.')] >> +ruleB;
        ruleB = ruleString >> ',' >> (ruleC % ',') >> ';';
        ruleC = qi::int_;

        ruleString = +qi::char_("a-z");

        BOOST_SPIRIT_DEBUG_NODES((ruleA)(ruleB)(ruleC)(ruleString))
    }
    qi::rule<Iterator, a_struct(), boost::spirit::ascii::space_type> ruleA;
    qi::rule<Iterator, b_struct(), boost::spirit::ascii::space_type> ruleB;
    qi::rule<Iterator, c_struct(), boost::spirit::ascii::space_type> ruleC;

    qi::rule<Iterator, std::string()/*, boost::spirit::ascii::space_type*/> ruleString;
};

int main() {
    std::string storage("parent ... whee,4,5,6;ahhhh,5,6;"); // We will read the contents here.

    typedef grammarA<std::string::const_iterator> grammarA_t;
    grammarA_t grammar;
    a_struct ast;

    std::string::const_iterator iter = storage.begin();
    std::string::const_iterator end = storage.end();

    bool r = phrase_parse(iter, end, grammar, boost::spirit::ascii::space, ast);

    if (r && iter == end) {
        std::cout << "Parsing succeeded" << std::endl;

        typedef std::back_insert_iterator<std::string> output_iterator_type;

        std::string generated;
        output_iterator_type sink(generated);

        typedef grammarB<output_iterator_type> grammarB_t;
        grammarB_t generator;

        if (generate_delimited(sink, generator, karma::space, ast))
        {
            std::cout << "'parent whee  ->  4  ->  5  ->  6 ahhhh  ->  5  ->  6 ' // ORIGINAL\n";
            std::cout << "'parent parent whee -> parent 4 -> parent 5 -> parent 6 ahhhh -> parent 5 -> parent 6 ' // DESIRED/EXPECTED\n";
            std::cout << "'" << generated << "' // ACTUAL" << std::endl;
        }
        else
            std::cout << "fail" << std::endl;
    }
}
