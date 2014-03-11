#include <string>
#include <iostream>
#include <typeinfo>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
 
int main()
{
  namespace qi = boost::spirit::qi;
 
  std::string input;
 
  std::cout << "Input a line: \n";
  //getline(std::cin, input);
  std::cout << "Got '" << input << "'.\n";
 
  unsigned count = 0;
  /*  
      Next, parse the input (input.c_str()),
      using a parser constructed with the following semantics
      (indentation matches source for clarity):
 
      Zero or more occurrences of (
          literal string "cat" ( when matched, increment the counter "count" )
      or  any character (to move on finding the next occurrence of "cat")
      )
  */
  auto rule = *(qi::lit("cat") [ ++qi::_val ] | qi::omit[qi::char_]);
  //qi::parse(input.begin(), input.end(), rule, count);
 
  /*
    The parser is constructed by the compiler using operator overloading and
    template matching, so the actual work is done within qi::parse(), and the
    expression starting with * only initializes the rule object that the parse
    function uses.
  */
 
  // last, show results.
  std::cout << typeid(rule).name();
}