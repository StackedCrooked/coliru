#include <iostream>
#include <vector>
#include <string>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_char.hpp>
#include <boost/spirit/include/qi_parse.hpp>
#include <boost/spirit/include/phoenix_bind.hpp>
using namespace boost::spirit;
using namespace boost::phoenix;
using std::endl;
using std::cout;
using std::string;
using std::vector;

void fPushOp(const string& op){
  cout << "PushOp: " << op << endl;
}

void fPushInt(string& my_str){
  cout << "PushInt: " << my_str << endl;
}

template<class Iterator, typename Skipper = qi::space_type>
struct Calculator : public qi::grammar<Iterator, Skipper> {

    qi::rule<Iterator, Skipper>  
      expression, logical_or_expression, logical_and_expression, negate_expression, series_expression,
      single_expression, inclusive_or_expression, exclusive_or_expression, and_expression, equality_expression, 
      relational_expression, shift_expression, additive_expression, multiplicative_expression, 
      term, complement_factor, factor, result;

    qi::rule<Iterator>  
      number, integer, variable, variable_combo, word;

    Calculator() : Calculator::base_type(result)
    {
          number = 
              lexeme[
                qi::as_string[
                    ("0x" >> +qi::char_("0-9a-fA-F"))     
                  | ("0b" >> +qi::char_("0-1"))
                  | ("0" >>  +qi::char_("0-7"))
                  | +qi::char_("0-9")
                ] [bind(&fPushInt, qi::_1)]
              ] 
             ;

          complement_factor = number
              | ('~' >> number)[bind(&fPushOp, "OP_COMPLEMENT")]
              | ('!' >> number)[bind(&fPushOp, "OP_NEGATE")];
              ;
          term = complement_factor
            >> *( (".." >> complement_factor)[bind(&fPushOp, "OP_LEGER")]
                | ('\\' >> complement_factor)[bind(&fPushOp, "OP_MASK")]
                ); 
          multiplicative_expression = term
            >> *( ('/' >> term)[bind(&fPushOp, "OP_DIV")]
                | ('%' >> term)[bind(&fPushOp, "OP_MOD")]
                | ('*' >> term)[bind(&fPushOp, "OP_MUL")]
                );
          additive_expression = multiplicative_expression
            >> *( ('+' >> multiplicative_expression)[bind(&fPushOp, "OP_ADD")]
                | ('-' >> multiplicative_expression)[bind(&fPushOp, "OP_SUB")]
                );
          shift_expression = additive_expression
            >> *( (">>" >> additive_expression)[bind(&fPushOp, "OP_SRL")]
                | ("<<" >> additive_expression)[bind(&fPushOp, "OP_SLL")]
                );
          relational_expression = shift_expression
            >> *( ('<' >> shift_expression)[bind(&fPushOp, "OP_LT")]
                | ('>' >> shift_expression)[bind(&fPushOp, "OP_GT")]
                | ("<=" >> shift_expression)[bind(&fPushOp, "OP_LET")]
                | (">=" >> shift_expression)[bind(&fPushOp, "OP_GET")]
                );
          equality_expression = relational_expression 
            >> *( ("==" >> relational_expression)[bind(&fPushOp, "OP_EQ")]
                | ("!=" >> relational_expression)[bind(&fPushOp, "OP_NEQ")] 
                );
          and_expression = equality_expression 
            >> *(('&' >> equality_expression)[bind(&fPushOp, "OP_AND")]); 
          exclusive_or_expression = and_expression 
            >> *(('^' >> and_expression)[bind(&fPushOp, "OP_XOR")]); 
          inclusive_or_expression = exclusive_or_expression 
            >> *(('|' >> exclusive_or_expression)[bind(&fPushOp, "OP_OR")]); 
          single_expression = inclusive_or_expression;
          series_expression = inclusive_or_expression 
            >> *((',' >> inclusive_or_expression)[bind(&fPushOp, "OP_SERIES")]);
          logical_and_expression = series_expression
            >> *(("&&" >> series_expression)[bind(&fPushOp, "OP_LOGICAL_AND")]); 
          logical_or_expression = logical_and_expression 
            >> *(("||" >> logical_and_expression)[bind(&fPushOp, "OP_LOGICAL_OR")]);
          expression = logical_or_expression;

          result = expression;
    }
};

int main(){
  Calculator<string::const_iterator> calc;
  const string expr("!3 && 0,1");
  string::const_iterator it = expr.begin();
  phrase_parse(it, expr.end(), calc, qi::space);
  cout << "Remaining: " << (string(it,expr.end())) << endl;

  return 0;
}
