#include <iostream>
#include <string>
#include <vector>

#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/spirit/include/qi.hpp>

namespace qi = boost::spirit::qi;



int main()
{
    std::string input = R"(
-- This is comment
ABC:= 121-XY1/7 > 45 OR SS >= 3
    ZY2 AND -- This is another comment
    (JKL * PQR) < 75;

JKL:= PP1 OR 
      PP2/2 XOR PP3;

ZZ_1:=A-B > 0 XOR (B2 % GH == 6 AND 
   SP == 4
-- Again a comment
    NOT AX > GF < 2 OR C*AS2 >= 5);
)";
    std::string::const_iterator iter = input.begin();
    std::string::const_iterator end = input.end();
    
    std::string stripped;

    bool result = qi::phrase_parse(iter, end,
                            +qi::char_, 
                            /*qi::space |*/"--" >> *(qi::char_ - qi::eol) >> qi::eol,
                            stripped);

    if(result && iter==end)
    {
        std::cout << "Success:" << stripped << std::endl;
    }
    else
    {
        std::cout << "Failure." << std::endl;
    }

    return 0;
}


