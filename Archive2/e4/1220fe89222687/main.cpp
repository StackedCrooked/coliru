#include <iostream>
#include <vector>

#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

namespace qi = boost::spirit::qi;

struct person 
{
   std::string name;
   uint8_t age; 
};

struct fruit
{
   std::string color;
   double average_weight;
};

BOOST_FUSION_ADAPT_STRUCT(
    person,
    (std::string, name)
    (uint8_t, age)
)

BOOST_FUSION_ADAPT_STRUCT(
    fruit,
    (std::string, color)
    (double, average_weight)
)

int main()
{
    std::string test="(jane, 23) (david, 19) (mary, 30) [yellow,100] [green, 60.6] [red, 30.5]";
    
    typedef std::string::const_iterator It;
    qi::rule<It,std::string()> string_rule = +~qi::char_(',');
    qi::rule<It,person(),qi::space_type> person_rule = '(' >> string_rule >> ',' >> qi::uint_ >> ')';
    qi::rule<It,fruit(),qi::space_type> fruit_rule = '[' >> string_rule >> ',' >> qi::double_ >> ']';
    
    It iter = test.begin(), end = test.end();
    
    std::vector<person> person_vector;
    std::vector<fruit> fruit_vector;
    
    bool result = qi::phrase_parse(iter, end, +person_rule >> +fruit_rule, qi::space, person_vector, fruit_vector);
    
    if(result && iter==end)
    {
        std::cout << "Success." << '\n';
        std::cout << "  Persons:" << '\n';
        for(const auto& person_ : person_vector)
            std::cout << "    " << person_.name << " is " << static_cast<int>(person_.age) << " years old." << '\n';
        std::cout << "  Fruits:" << '\n';
        for(const auto& fruit_ : fruit_vector)
            std::cout << "    A " << fruit_.color << " fruit that weighs " << fruit_.average_weight << '\n';
        std::cout << std::endl;
    }
    else
    {
        std::cout << "Failure, unparsed: " << std::string(iter,end) << std::endl;
    }
}



