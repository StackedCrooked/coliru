#include <string>
#include <vector>
#include <iostream>

#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/phoenix_statement.hpp>
#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/spirit/include/phoenix_function.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/variant.hpp>
#include <boost/variant/recursive_wrapper.hpp>
#include <boost/array.hpp>
#include <boost/variant/apply_visitor.hpp>

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace phoenix = boost::phoenix;

namespace client {
  typedef std::string::iterator input_iterator_type;

  struct op_and {}; 
  struct op_or {};
  struct op_eq {};
  struct op_neq {};
  struct is_part_of {};
  struct more {};
  struct more_eq {};
  struct less {};
  struct less_eq {};
  struct mask_match {};
  struct mask_not_match {};
  struct in {};

 namespace type {
    enum code_t {
      string       = 0,
      boolean      = 1,
      number       = 2,
      none         = 3,
      datetime     = 4,
      unknown      = 5
    }; 
  }

  template <typename tag>  struct binop;
  struct   fn_call;
  struct   none_type {~none_type(){}};

  struct datetime {
    datetime(int yyyy, int mm, int dd, int hh24, int mi, int ss, int mls) 
      : yy(yyyy), mm(mm), dd(dd), hh(hh24), mi(mi), ss(ss), ms(mls) {}
    datetime()
      : yy(0), mm(0), dd(0), hh(0), mi(0), ss(0), ms(0) {}
    int yy; int mm; int dd;
    int hh; int mi; int ss;
    int ms;
  };

  typedef boost::variant<
    boost::recursive_wrapper<binop<op_and> >,
    boost::recursive_wrapper<binop<op_or> >,
    boost::recursive_wrapper<binop<op_eq> >,
    boost::recursive_wrapper<binop<op_neq> >,
    boost::recursive_wrapper<binop<is_part_of> >,
    boost::recursive_wrapper<binop<more> >,
    boost::recursive_wrapper<binop<more_eq> >,
    boost::recursive_wrapper<binop<less> >,
    boost::recursive_wrapper<binop<less_eq> >,
    boost::recursive_wrapper<binop<mask_match> >,
    boost::recursive_wrapper<binop<mask_not_match> >,
    boost::recursive_wrapper<binop<in> >
  > generic_binop;

  typedef boost::variant <
    std::string, double, none_type, datetime,
    boost::recursive_wrapper<generic_binop>,
    boost::recursive_wrapper<fn_call>
  > node_value_t;

  struct g_node {
    mutable type::code_t type_id; 
    mutable node_value_t value;
  };

  typedef node_value_t value_type;

  template <typename tag> struct binop { 
    explicit binop(const g_node& l, const g_node& r) 
      : oper1(l), oper2(r) {}
    g_node oper1, oper2; 
  };

  typedef std::vector<g_node> node_vector;

  struct fn_call {
    explicit fn_call(){}
    std::string name;
    node_vector params;
  };
}

BOOST_FUSION_ADAPT_STRUCT(
client::g_node,
(client::type::code_t, type_id)
(client::node_value_t, value)
)

BOOST_FUSION_ADAPT_STRUCT(
client::fn_call,
(std::string, name)
(std::vector<client::g_node>, params)
)

namespace client {

  template <typename Iterator> struct g_error_handler {
   template<typename, typename, typename, typename> 
    struct result { typedef void type; };

    void operator()(Iterator first, Iterator last,
          Iterator err_pos, boost::spirit::info const& what) const { 
      std::cout << "Syntax error. Expected: " << what << " at: " << 
        std::distance(first, err_pos) << std::endl;
    }
};

  template<typename Iterator, typename ErrorHandler = g_error_handler<Iterator> >
  struct g_parser : qi::grammar<Iterator, g_node(), ascii::space_type> {
    g_parser() : g_parser::base_type(or_, "G"), error_handler(ErrorHandler()) {

      using phoenix::at_c;

      or_ = (and_ >> "||" >> or_)[
        at_c<0>(qi::_val) = type::unknown, 
        at_c<1>(qi::_val) = phoenix::construct<binop<op_or> >(qi::_1, qi::_2)] |
        and_[qi::_val = qi::_1];

      and_ = (bool_op >> "&&" >> and_)[
        at_c<0>(qi::_val) = type::unknown, 
        at_c<1>(qi::_val) = phoenix::construct<binop<op_and> >(qi::_1, qi::_2)] |
        bool_op[qi::_val = qi::_1];

      using boost::phoenix::construct;
      bool_op = 
          prim [ qi::_val = qi::_1 ]
          >> -((
          ("="  >> bool_op [ at_c<1>(qi::_val) = construct<binop<op_eq> >          (qi::_val, qi::_1) ]) | 
          ("<>" >> bool_op [ at_c<1>(qi::_val) = construct<binop<op_neq> >         (qi::_val, qi::_1) ]) | 
          (":"  >> bool_op [ at_c<1>(qi::_val) = construct<binop<is_part_of> >     (qi::_val, qi::_1) ]) | 
          (">"  >> bool_op [ at_c<1>(qi::_val) = construct<binop<more> >           (qi::_val, qi::_1) ]) | 
          (">=" >> bool_op [ at_c<1>(qi::_val) = construct<binop<more_eq> >        (qi::_val, qi::_1) ]) | 
          ("<"  >> bool_op [ at_c<1>(qi::_val) = construct<binop<less> >           (qi::_val, qi::_1) ]) | 
          ("<=" >> bool_op [ at_c<1>(qi::_val) = construct<binop<less_eq> >        (qi::_val, qi::_1) ]) | 
          ("=~" >> bool_op [ at_c<1>(qi::_val) = construct<binop<mask_match> >     (qi::_val, qi::_1) ]) | 
          ("!~" >> bool_op [ at_c<1>(qi::_val) = construct<binop<mask_not_match> > (qi::_val, qi::_1) ]) | 
          ("in" >> bool_op [ at_c<1>(qi::_val) = construct<binop<in> >             (qi::_val, qi::_1) ])
          ) >> qi::eps [ at_c<0>(qi::_val) = type::unknown ])
          ;

       prim = 
         string_val   [qi::_val =  qi::_1] |
         number       [qi::_val =  qi::_1] |
         func_call    [at_c<0>(qi::_val) = type::unknown, at_c<1>(qi::_val) =  qi::_1] | 
         ('(' > or_    [qi::_val =  qi::_1] > ')');

       quoted_string %= "'" > qi::lexeme[*(qi::char_ - "'")] > "'";

       func_call = fn_name > '(' > -(or_ % ',') > ')';
       fn_name %= +(qi::alpha) > -(qi::char_('-')) > *(qi::alnum);

       string_val = quoted_string[
         at_c<0>(qi::_val) = type::string, at_c<1>(qi::_val) = qi::_1];

       number %= qi::attr(type::number) >> qi::double_;

       or_.name           ("OR expression"  );
       and_.name          ("AND expression" );
       bool_op.name       ("BOOL expression");
       prim.name          ("Atom expression");
       quoted_string.name ("quoted string"  );
       fn_name.name       ("function name"  );
       number.name        ("number"         );

       qi::on_error<qi::fail>(or_, error_handler(qi::_1, qi::_2, qi::_3, qi::_4));
    }

    qi::rule<Iterator, g_node(), ascii::space_type> 
      and_, prim, bool_op, or_, string_val, number;
    qi::rule<Iterator, fn_call(), ascii::space_type> func_call;
    qi::rule<Iterator, std::string(), ascii::space_type> quoted_string, fn_name;

    boost::phoenix::function<ErrorHandler> error_handler;
  };

  typedef g_parser<input_iterator_type> grammar;
}

int main() {
    std::string s = "((foo(bar('','')) = foo('')) || ('a' = 'gg')) && (3 <> 7) && (foo('','') = bar('','')) && 2=4 && 'a' ='b' && foo('') <> foo('')";
    client::grammar g;
    client::g_node ast;
    std::string::iterator begin = s.begin();
    std::string::iterator end = s.end();
    bool success = qi::phrase_parse(begin, end, g, 
            boost::spirit::ascii::space, ast) && begin == end;
    std::stringstream ss;
    if(!success)
        std::cout << "Syntax error at: " << std::distance(s.begin(), begin);
    else std::cout << "Syntax is Ok\n";
}
