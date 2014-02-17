#include <boost/any.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/fusion/include/define_struct.hpp>
#include <boost/fusion/adapted.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/variant.hpp>

#include <iostream>
#include <string>
#include <vector>

namespace qi = boost::spirit::qi;
// Helper structs

// types

enum class types { void_t, int_t, double_t, bool_t, string_t };

struct types_ : qi::symbols<char, types>
{
  types_()
  {
    add
      ("void"    , types::void_t)
      ("int"     , types::int_t)
      ("double"  , types::double_t)
      ("bool"    , types::bool_t)
      ("string"  , types::string_t)
    ;
  }
} type;

inline
std::ostream& operator<<(std::ostream& os, const types& type)
{
  switch (type)
  {
  case types::void_t:
    os << "void";
    break;

  case types::int_t:
    os << "int";
    break;

  case types::double_t:
    os << "double";
    break;

  case types::bool_t:
    os << "bool";
    break;

  case types::string_t:
    os << "string";
    break;
  }

  return os;
}

// assignment_operators

enum class assignment_operators { basic, addition, subtraction, multiplication, division, modulo, bitwise_and, bitwise_or, bitwise_xor, bitwise_left_shift, bitwise_right_shift };

struct assignment_operators_ : boost::spirit::qi::symbols<char, assignment_operators>
{
  assignment_operators_()
  {
    add
      ("="    , assignment_operators::basic)
      ("+="   , assignment_operators::addition)
      ("-="   , assignment_operators::subtraction)
      ("*="   , assignment_operators::multiplication)
      ("/="   , assignment_operators::division)
      ("%="   , assignment_operators::modulo)
      ("&="   , assignment_operators::bitwise_and)
      ("|="   , assignment_operators::bitwise_or)
      ("^="   , assignment_operators::bitwise_xor)
      ("<<="  , assignment_operators::bitwise_left_shift)
      (">>="  , assignment_operators::bitwise_right_shift)
    ;
  }
} assignment_operator;

inline
std::ostream& operator<<(std::ostream& os, const assignment_operators& assignment_operator)
{
  switch (assignment_operator)
  {
  case assignment_operators::basic:
    os << "=";
    break;

  case assignment_operators::addition:
    os << "+=";
    break;

  case assignment_operators::subtraction:
    os << "-=";
    break;

  case assignment_operators::multiplication:
    os << "*=";
    break;

  case assignment_operators::division:
    os << "/=";
    break;

  case assignment_operators::modulo:
    os << "%=";
    break;

  case assignment_operators::bitwise_and:
    os << "&=";
    break;

  case assignment_operators::bitwise_or:
    os << "|=";
    break;

  case assignment_operators::bitwise_xor:
    os << "^=";
    break;

  case assignment_operators::bitwise_left_shift:
    os << "<<=";
    break;

  case assignment_operators::bitwise_right_shift:
    os << ">>=";
    break;
  }

  return os;
}

// relational_operators

enum class relational_operators { equal_to, not_equal_to, greater_than, less_than, greater_than_or_equal_to, less_than_or_equal_to };

struct relational_operators_ : boost::spirit::qi::symbols<char, relational_operators>
{
  relational_operators_()
  {
    add
      ("=="  , relational_operators::equal_to)
      ("!="  , relational_operators::not_equal_to)
      (">"   , relational_operators::greater_than)
      ("<"   , relational_operators::less_than)
      (">="  , relational_operators::greater_than_or_equal_to)
      ("<="  , relational_operators::less_than_or_equal_to)
    ;
  }
} relational_operator;

inline
std::ostream& operator<<(std::ostream& os, const relational_operators& relational_operator)
{
  switch (relational_operator)
  {
  case relational_operators::equal_to:
    os << "==";
    break;

  case relational_operators::not_equal_to:
    os << "!=";
    break;

  case relational_operators::greater_than:
    os << ">";
    break;

  case relational_operators::less_than:
    os << "<";
    break;

  case relational_operators::greater_than_or_equal_to:
    os << ">=";
    break;

  case relational_operators::less_than_or_equal_to:
    os << "<=";
    break;
  }

  return os;
}

// parameter

BOOST_FUSION_DEFINE_STRUCT(
  (), parameter,
  (types, type)
  (std::string, name)
)

// function_call

BOOST_FUSION_DEFINE_STRUCT(
  (), function_call,
  (std::string, name)
  (std::vector<boost::any>, actual_parameters)
)

// variable_definition

BOOST_FUSION_DEFINE_STRUCT(
  (), variable_definition,
  (std::string, name)
  (boost::any, initializer)
)

// variables_definitions

BOOST_FUSION_DEFINE_STRUCT(
  (), variables_definitions,
  (types, type)
  (std::vector<::variable_definition>, variables)
)

// return_expression

BOOST_FUSION_DEFINE_STRUCT(
  (), return_statement,
  (boost::any, value)
)

// assignment_expression

BOOST_FUSION_DEFINE_STRUCT(
  (), assignment_expression,
  (std::string, name)
  (assignment_operators, op)
  (boost::any, value)
)

// relational_expression

BOOST_FUSION_DEFINE_STRUCT(
  (), relational_expression,
  (boost::any, left)
  (relational_operators, op)
  (boost::any, right)
)

// function

typedef boost::any expressions_types;

BOOST_FUSION_DEFINE_STRUCT(
  (), function,
  (types, ret_type)
  (std::string, name)
  (std::vector<parameter>, parameters)
  (std::vector<expressions_types>, expressions)
)

// preprocessor_directive

BOOST_FUSION_DEFINE_STRUCT(
  (), include_preprocessor_directive,
  (std::string, file)
)

BOOST_FUSION_DEFINE_STRUCT(
  (), define_preprocessor_directive,
  (std::string, name)
  (boost::any, value)
)

BOOST_FUSION_DEFINE_STRUCT(
  (), property_preprocessor_directive,
  (std::string, name)
  (boost::any, value)
)

typedef boost::variant<::include_preprocessor_directive, ::define_preprocessor_directive, ::property_preprocessor_directive> preprocessor_directives_t;

// mql source

typedef boost::variant<::function, preprocessor_directives_t, ::variables_definitions> mql_source_elements_types;

BOOST_FUSION_DEFINE_STRUCT(
  (), mql_source,
  (std::vector<mql_source_elements_types>, mql_source_elements)
)

template <typename Iterator, typename Skipper>
struct mql_parser : qi::grammar<Iterator, mql_source(), Skipper>
{
  mql_parser() : mql_parser::base_type(start_)
  {
    identifier_                      %= qi::alpha >> *qi::alnum;                                                                             // foo, bar, some1var
    literal_                         %= qi::int_                                                                                             // 1
                                     | qi::double_                                                                                           // 1.5
                                     | qi::bool_                                                                                             // true
                                     | ('\'' >> qi::char_ >> '\'')                                                                           // 's'
                                     | qi::as_string[qi::lexeme['"' >> +(qi::char_ - '"') >> '"']];                                          // "str"
    relational_expression_           %= expression_ >> relational_operator >> expression_;                                                   // i == 0
    assignment_expression_           %= identifier_ >> assignment_operator >> expression_;                                                   // i = 1
    expression_                      %= relational_expression_ | identifier_ | function_call_ | literal_ | ('(' >> expression_ >> ')');
    function_call_                   %= identifier_ >> '(' >> (expression_ % ',') >> ')';
    variable_definition_             %= identifier_ >> -('=' >> expression_);                                                                // int i = 0
    variables_definitions_           %= type >> (variable_definition_ % ',');                                                                // int i = 0, j = 1
    return_statement_                %= "return" >> -(expression_);

    param_                           %= type >> -identifier_;
    function_definition_             %= type >> identifier_ >> '(' >> (param_ % ',') >> ')' >> '{' >> (expression_ % ';') >> ';' >> '}';     // void foo(int bar, double) { foo(); int i = 0; }
    include_preprocessor_directive_  %= '#' >> qi::lit("include") >> qi::lexeme[+qi::graph];                                                 // #include <WinUser32.mqh>
    define_preprocessor_directive_   %= '#' >> qi::lit("define") >> identifier_ >> literal_;                                                 // #define FOO 0
    property_preprocessor_directive_ %= '#' >> qi::lit("property") >> identifier_ >> -literal_;                                              // #property stacksize 1024
    preprocessor_directive_          %= include_preprocessor_directive_ | define_preprocessor_directive_ | property_preprocessor_directive_; // #include <WinUser32.mqh>
    start_                           %= qi::eps >> +(function_definition_ | preprocessor_directive_ | (variables_definitions_ >> ';'));      // void foo(int bar, double) { foo(); } void bar(int baz, double) { foo(); }

  }

  qi::rule<Iterator, std::string()                                          > identifier_;
  qi::rule<Iterator, parameter()                                   , Skipper> param_;
  qi::rule<Iterator, function_call()                               , Skipper> function_call_;
  qi::rule<Iterator, boost::any()                                  , Skipper> literal_;
  qi::rule<Iterator, variable_definition()                         , Skipper> variable_definition_;
  qi::rule<Iterator, variables_definitions()                       , Skipper> variables_definitions_;
  qi::rule<Iterator, return_statement()                            , Skipper> return_statement_;
  qi::rule<Iterator, assignment_expression()                       , Skipper> assignment_expression_;
  qi::rule<Iterator, relational_expression()                       , Skipper> relational_expression_;
  qi::rule<Iterator, expressions_types()                           , Skipper> expression_;
  qi::rule<Iterator, function()                                    , Skipper> function_definition_;
  qi::rule<Iterator, include_preprocessor_directive()              , Skipper> include_preprocessor_directive_;
  qi::rule<Iterator, define_preprocessor_directive()               , Skipper> define_preprocessor_directive_;
  qi::rule<Iterator, property_preprocessor_directive()             , Skipper> property_preprocessor_directive_;
  qi::rule<Iterator, preprocessor_directives_t()                   , Skipper> preprocessor_directive_;
  qi::rule<Iterator, mql_source()                                  , Skipper> start_;
};

std::string get_file_content(const boost::filesystem::path& file_path)
{
  std::string file_content;

  boost::filesystem::ifstream f(file_path);
  if (f)
  {
    file_content.append(
      (std::istreambuf_iterator<char>(f))
      , std::istreambuf_iterator<char>()
    );
  }

  return file_content;
}

int main()
{
    const std::string& input_data = get_file_content("input.txt");

    mql_source mql_src;
    auto itr = input_data.begin();
    auto end = input_data.end();

    qi::rule<decltype(itr)> skipper = 
        qi::ascii::space 
        | ("//" >> *(qi::char_ - qi::eol) >> qi::eol | qi::blank)
        | ("/*" >> *(qi::char_ - "*/") >> "*/");

    mql_parser<decltype(itr), decltype(skipper)> g;

    bool res = qi::phrase_parse(
            itr
            , end
            , g
            , skipper
            , mql_src
            );
    if (res && itr == end)
    {
        std::cout << "Parsing succeeded \n";
    }
    else
    {
        std::cout << "Parsing failed \n";
    }
}

