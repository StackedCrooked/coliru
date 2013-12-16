#include <iostream>
#include <string>
#include <vector>

#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/at.hpp>

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace fusion = boost::fusion;

int main()
{
    typedef std::string::const_iterator Iter;
    
    qi::rule<Iter, std::string(), ascii::space_type> attr;
    attr = qi::lexeme[*ascii::alnum];
    qi::rule<Iter,std::string(), ascii::space_type> string_rule;
    string_rule='(' >> qi::lit("str") >> attr >> ')';
    qi::rule<Iter,float(), ascii::space_type> float_rule;
    float_rule='(' >> qi::lit("n") >> qi::float_ >> ')';
    qi::rule<Iter, fusion::vector2<std::string, float>(), ascii::space_type> hj;
    hj = string_rule ^ float_rule;
         
    std::vector<std::string> tests;
    tests.push_back("(str foo)(n 12.3)");
    tests.push_back("(n 23.4)(str bar)");
    tests.push_back("(n 34.5)");
    tests.push_back("(str baz)");
    
    
    for(std::size_t n=0; n<tests.size(); ++n)
    {
        Iter iter=tests[n].begin(), end=tests[n].end();
        
        fusion::vector2<std::string,float>  parsed;
        
        bool result = qi::phrase_parse(iter,end,hj,ascii::space,parsed);
        
        if(result && iter==end)
        {
            std::cout << '"' << tests[n] << "\" has been parsed successfully:" << std::endl;
            std::cout << "[\"" << fusion::at_c<0>(parsed) << "\", " << fusion::at_c<1>(parsed) << "]" << std::endl;
        }
        else
        {
            std::cout << "Error, unparsed: " << std::string(iter,end) << std::endl;
        }
    }
}
