#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_core.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/spirit/repository/include/qi_kwd.hpp>
 
struct Parameters
{
    std::vector<std::string> Genre;
    std::vector<std::string> Social;
    std::vector<std::string> Tag;
    std::size_t Page;
};
 
BOOST_FUSION_ADAPT_STRUCT
(
    Parameters,
    (std::vector<std::string>, Genre)
    (std::vector<std::string>, Social)
    (std::vector<std::string>, Tag)
    (std::size_t, Page)
)
 
template<typename Iterator>
class Parser : qi::grammar<Iterator, Parameters(), ascii::space_type>
{
public:
    Parser() : Parser::base_type(parameterRule_)
    {
        using boost::spirit::repository::qi::kwd;
 
        parserParameter_   %= *(boost::spirit::ascii::char_-'&');
 
        parameterRule_ %=
                  kwd("g")  ['=' > parserParameter_]
                / kwd("s")  ['=' > parserParameter_]
                / kwd("t")  ['=' > parserParameter_]
                / kwd("p", 0, 1)    ['=' > parserParameter_]
                ;
    }
private:
    boost::spirit::qi::rule<const char *, std::string(), boost::spirit::ascii::space_type> parserParameter_;
    boost::spirit::qi::rule<const char *, Parameters(), boost::spirit::ascii::space_type> parameterRule_;
};

int main()
{
    namespace qu = boost::spirit::qi;
    
    std::string str = "g=abc&s=def&t=qwerty&p=1";
    using iter = std::string::const_iterator;
    
    Parameters params;
    Parser<iter> par;
    iter begin = str.begin();
    iter end = str.end();
    bool result = qi::phrase_parse(begin,end,par,qi::space,par);
}