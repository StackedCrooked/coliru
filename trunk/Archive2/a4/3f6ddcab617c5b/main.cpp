#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/repository/include/qi_kwd.hpp>
#include <boost/spirit/repository/include/qi_keywords.hpp>
#include <iostream>
#include <string>

namespace qi  = boost::spirit::qi;
namespace phx = boost::phoenix;
namespace rqi = boost::spirit::repository::qi;

template <typename Iterator>
bool difference(Iterator first, Iterator last, double& n) {
    bool r = boost::spirit::qi::phrase_parse(first, last,
             //the grammar
             (rqi::kwd("A") [qi::double_ [phx::ref(n) += qi::_1]] / 
              rqi::kwd("B") [qi::double_ [phx::ref(n) -= qi::_1]]), boost::spirit::ascii::space);

    if (first != last) return false;
    return r;
}

int main() {
    std::string str("A 1 B 2");
    double n=0;
    std::cout << "Full parse: " << difference(str.begin(), str.end(), n) << std::endl;  
    std::cout << "A - B = " << n <<std::endl;
    return 0;
}