#include <iostream>
#include <string>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
namespace qi = boost::spirit::qi;
namespace phx = boost::phoenix;

void fPushOp(const std::string& op){
    std::cout << "PushOp: " << op << std::endl;
}

void fPushInt(std::string& my_str){
    std::cout << "PushInt: " << my_str << std::endl;
}

template<class Iterator, typename Skipper = qi::space_type>
struct Calculator : public qi::grammar<Iterator, Skipper> {

    qi::rule<Iterator, Skipper>  
      expression, logical_or_expression, logical_and_expression,
        negate_expression, series_expression, single_expression,
        inclusive_or_expression, exclusive_or_expression, and_expression,
        equality_expression, relational_expression, shift_expression,
        additive_expression, multiplicative_expression, term,
        complement_factor, factor, result;

    qi::rule<Iterator>  
        number, integer, variable, variable_combo, word;

    Calculator() : Calculator::base_type(result)
    {
        using namespace qi;

        number = 
            lexeme[
              qi::as_string[
                  ("0x" >> +qi::char_("0-9a-fA-F"))     
                | ("0b" >> +qi::char_("0-1"))
                | ("0" >>  +qi::char_("0-7"))
                | +qi::char_("0-9")
              ] [phx::bind(&fPushInt, qi::_1)]
            ] 
           ;

        complement_factor = number
            | ('~' >> number)[phx::bind(&fPushOp, "OP_COMPLEMENT")]
            | ('!' >> number)[phx::bind(&fPushOp, "OP_NEGATE")];
            ;
        term = complement_factor
          >> *( (".." >> complement_factor)[phx::bind(&fPushOp, "OP_LEGER")]
              | ('\\' >> complement_factor)[phx::bind(&fPushOp, "OP_MASK")]
              ); 
        multiplicative_expression = term
          >> *( ('/' >> term)[phx::bind(&fPushOp, "OP_DIV")]
              | ('%' >> term)[phx::bind(&fPushOp, "OP_MOD")]
              | ('*' >> term)[phx::bind(&fPushOp, "OP_MUL")]
              );
        additive_expression = multiplicative_expression
          >> *( ('+' >> multiplicative_expression)[phx::bind(&fPushOp, "OP_ADD")]
              | ('-' >> multiplicative_expression)[phx::bind(&fPushOp, "OP_SUB")]
              );
        shift_expression = additive_expression
          >> *( (">>" >> additive_expression)[phx::bind(&fPushOp, "OP_SRL")]
              | ("<<" >> additive_expression)[phx::bind(&fPushOp, "OP_SLL")]
              );
        relational_expression = shift_expression
          >> *( ('<' >> shift_expression)[phx::bind(&fPushOp, "OP_LT")]
              | ('>' >> shift_expression)[phx::bind(&fPushOp, "OP_GT")]
              | ("<=" >> shift_expression)[phx::bind(&fPushOp, "OP_LET")]
              | (">=" >> shift_expression)[phx::bind(&fPushOp, "OP_GET")]
              );
        equality_expression = relational_expression 
          >> *( ("==" >> relational_expression)[phx::bind(&fPushOp, "OP_EQ")]
              | ("!=" >> relational_expression)[phx::bind(&fPushOp, "OP_NEQ")] 
              );
        and_expression = equality_expression 
          >> *(('&' >> equality_expression)[phx::bind(&fPushOp, "OP_AND")]); 
        exclusive_or_expression = and_expression 
          >> *(('^' >> and_expression)[phx::bind(&fPushOp, "OP_XOR")]); 
        inclusive_or_expression = exclusive_or_expression 
          >> *(('|' >> exclusive_or_expression)[phx::bind(&fPushOp, "OP_OR")]); 
        single_expression = inclusive_or_expression;
        series_expression = inclusive_or_expression 
          >> *((',' >> inclusive_or_expression)[phx::bind(&fPushOp, "OP_SERIES")]);
        logical_and_expression = series_expression
          >> *(("&&" >> series_expression)[phx::bind(&fPushOp, "OP_LOGICAL_AND")]); 
        logical_or_expression = logical_and_expression 
          >> *(("||" >> logical_and_expression)[phx::bind(&fPushOp, "OP_LOGICAL_OR")]);
        expression = logical_or_expression;

        result = expression;
    }
};

int main(){
  Calculator<std::string::const_iterator> calc;

  const std::string expr("!3 && 0,1");
  std::string::const_iterator it = expr.begin();

  phrase_parse(it, expr.end(), calc, qi::space);

  std::cout << "Remaining: " << std::string(it,expr.end()) << std::endl;

  return 0;
}
