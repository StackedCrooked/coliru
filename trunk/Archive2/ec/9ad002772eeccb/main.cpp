#include <iostream>
#include <string>

#define BOOST_RESULT_OF_USE_TR1
//#define BOOST_SPIRIT_USE_PHOENIX_V3

#include <boost/spirit/include/qi.hpp>

namespace qi = boost::spirit::qi;
namespace encoding = boost::spirit::ascii;
using boost::spirit::unused_type;
using boost::spirit::qi::rule;

template <typename Iterator>
struct cparser : qi::grammar<
                    Iterator,
                    std::string(std::string),
                    encoding::space_type
                    >
{
    rule<Iterator, std::string(std::string), encoding::space_type> start;
    rule<Iterator, std::string(std::string), encoding::space_type> sym_list;

    cparser() :
        cparser::base_type(start)
    {
        sym_list         = encoding::string(boost::spirit::qi::_r1);
        start            = sym_list(boost::spirit::qi::_r1);
    }

};

template <typename Parser>
void parse(const std::string& test, const Parser& parser)
{
    std::string::const_iterator iter=test.begin(), end=test.end();    
    
    bool result = qi::phrase_parse(iter,end,parser,encoding::space);
    
    if(result && iter==end)
    {
        std::cout << "Success." << std::endl;
    }
    else
    {
        std::cout << "Failure." << std::endl;
    }
}

int main()
{
    std::string test="foo";
    
    cparser<std::string::const_iterator> parser;

    parse(test,parser(std::string("bla")));
    parse(test,parser(std::string("foo")));
}