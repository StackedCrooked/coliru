#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/adapt_adt.hpp>
#include <fstream>

  struct c_struct
  {
    int value1;
  };
  
  struct b_struct
  {
    std::string value1;
    std::vector< c_struct > value2;
  };
  
  struct a_struct
  { 
    std::string value1;
    std::vector< b_struct > value2;
  };
  
BOOST_FUSION_ADAPT_STRUCT( c_struct,    
    (int, value1)
)

BOOST_FUSION_ADAPT_STRUCT( b_struct,    
    (std::string, value1)
    (std::vector< c_struct >, value2)
)

BOOST_FUSION_ADAPT_STRUCT( a_struct,    
    (std::string, value1)
    (std::vector< b_struct >, value2)
)

using namespace boost::spirit;
using namespace boost::spirit::qi;
using namespace boost::spirit::karma;
using namespace boost::spirit::ascii;

template <typename Iterator>
struct grammarB : karma::grammar<Iterator, a_struct()>
{
  grammarB() : grammarB::base_type(ruleA)
  {
    ruleA %= karma::string << karma::lit(' ') << +ruleB << eps;
    ruleB %= karma::string << +ruleC << karma::lit(' ') << eps;    
    ruleC %= lit("  ->  ") << karma::int_;
  }
  
  karma::rule<Iterator, a_struct()> ruleA;
  karma::rule<Iterator, b_struct()> ruleB;
  karma::rule<Iterator, c_struct()> ruleC;
};

template <typename Iterator>
struct grammarA : qi::grammar<Iterator, a_struct(), boost::spirit::ascii::space_type>
{
  grammarA() : grammarA::base_type(ruleA)
  {
    ruleA %= ruleString >> omit[+qi::char_('.')] >> +ruleB;
    ruleB %= ruleString >> omit[qi::char_(',')] >> (ruleC % qi::char_(',')) >> omit[qi::char_(';')];
    ruleC %= qi::int_;
    
    ruleString %= +qi::char_("a-z");
  }           
  qi::rule<Iterator, a_struct(), boost::spirit::ascii::space_type> ruleA;   
  qi::rule<Iterator, b_struct(), boost::spirit::ascii::space_type> ruleB;  
  qi::rule<Iterator, c_struct(), boost::spirit::ascii::space_type> ruleC;
  
  qi::rule<Iterator, std::string(), boost::spirit::ascii::space_type> ruleString;
};    
  
int main(int argc, char **argv)
{   
  std::string storage("parent ... whee,4,5,6;ahhhh,5,6;"); // We will read the contents here.
   
  typedef grammarA<std::string::const_iterator> grammarA_t;
  grammarA_t grammar;
  a_struct ast;
  
  std::string::const_iterator iter = storage.begin();
  std::string::const_iterator end = storage.end();
 
  bool r = phrase_parse(iter, end, grammar, boost::spirit::ascii::space, ast);

  if (r && iter == end)
  {    
    std::cout << "Parsing succeeded" << std::endl;
    
    typedef std::back_insert_iterator<std::string> output_iterator_type;
           
    std::string generated;    
    output_iterator_type sink(generated);
            
    typedef grammarB<output_iterator_type> grammarB_t; 
    grammarB_t generator;
    
    
    if ( generate(sink, generator, ast) )
        std::cout << generated << std::endl;
    else
        std::cout << "fail" << std::endl;
  }
  
  return 0;
}