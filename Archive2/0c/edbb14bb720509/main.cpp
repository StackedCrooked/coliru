#include <boost/spirit/include/qi.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_bind.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/preprocessor.hpp>

#include <iostream>
#include <string>
#include <unordered_map>

namespace predicate {




template <typename T>
struct properties {
    static std::unordered_map<std::string,T> storage;
    static std::unordered_map<std::string,bool> is_stored;

    static bool get_obj(const std::string& key,T& val){
        val = storage[key];
        return is_stored[key];
    }
    
    static void create (const std::string& key,const T& val){
        is_stored[key] = true;
        storage[key] = val;
    }
};

template<typename T> 
std::unordered_map<std::string,T> properties<T>::storage;

template<typename T> 
std::unordered_map<std::string,bool> properties<T>::is_stored;

struct object{
};

//typedef boost::function<bool (const object &obj)> bool_func;
//typedef boost::function<int (const object &obj)> int_func;

template<typename T>
using func = boost::function<T (const object& obj)>;

typedef func<bool> bool_func; 
typedef func<int>  int_func;

bool u_op_not(const bool_func &a, const object &obj) {
    return !a(obj);
}

bool op_or(const bool_func &a, const bool_func &b, const object &obj) {
    return a(obj) || b(obj);
}
bool op_and(const bool_func &a, const bool_func &b, const object &obj) {
    return a(obj) && b(obj);
}

bool_func make_logic_op(bool (*f)(const bool_func &, const bool_func &, const object &),
    const bool_func &a, const bool_func &b)
{
    return boost::bind(f, a, b, _1);
}

bool_func make_cmp_op(bool (*f)(const int_func &, const int_func &, const object &),
    const int_func &a, const int_func &b)
{
    return bind(f, a, b, _1);
}

bool_func make_not(const bool_func &a) {
    return boost::bind(&u_op_not, a, _1);
}

template <typename T>
T rep(T x) {return x;}

template<typename T>
func<T> make_const(T x){
    return boost::bind(&rep<T>,x);
}


template <typename T>
func<T> make_prop_reader(const std::string& st, bool& is_pass){
    T val;
    if (properties<T>::get_obj(st,val)){
        return make_const(val);
    }
    is_pass = false;
    return func<T>();
}

#define CMP_OP(OP,NAME)                                                         \
    bool NAME(const int_func &a, const int_func &b, const object &obj) {        \
        return a(obj) OP b(obj);                                                \
    }
#define CMP_OP_ELEM(n,data,elem) CMP_OP elem 
#define CREATE_OPERATIONS(SEQ)  BOOST_PP_SEQ_FOR_EACH(CMP_OP_ELEM,_,SEQ)

CREATE_OPERATIONS(
                ((<,op_less))
                ((<=,op_less_eq))
                ((>,op_greater))
                ((>=,op_greater_eq))
                ((==,op_eq))
                ((!=,op_not_eq))
                )
        
using namespace boost::spirit;

template <class I, class S> 
struct predicate_grammar :
    qi::grammar<I, bool_func(), S>
{
    predicate_grammar() : predicate_grammar::base_type(bool_expr)
    {
        using boost::spirit::int_;
        using boost::spirit::ascii::string;
        using boost::spirit::ascii::char_;
        using namespace qi::labels;
        namespace ph = boost::phoenix;
        
        identifier = char_("a-z") >> *(char_("a-z_0-9"));
        bool_prop = identifier [ _val = ph::bind(&make_prop_reader<bool>, qi::_1, _pass) ];
        bool_expr = (bool_expr2 >> "||" >> bool_expr) [ _val = ph::bind(&make_logic_op, &op_or, qi::_1, qi::_2) ]
                  | bool_expr2 [ _val = qi::_1 ];
        bool_expr2 = (bool_expr3 >> "&&" >> bool_expr2) [ _val = ph::bind(&make_logic_op, &op_and, qi::_1, qi::_2) ]
                   | bool_expr3 [ _val = qi::_1 ];
        bool_expr3 = ('(' >> bool_expr >> ')') [ _val = qi::_1 ]
                   | ('!' >> bool_expr3) [ _val = ph::bind(&make_not, qi::_1) ]
                   | int_comp [ _val = qi::_1 ]
                   | bool_prop [ _val = qi::_1];
        int_comp = (int_expr >> "<"  >> int_expr) [ _val = ph::bind(&make_cmp_op, &op_less,       qi::_1, qi::_2) ]
                 | (int_expr >> "<=" >> int_expr) [ _val = ph::bind(&make_cmp_op, &op_less_eq,    qi::_1, qi::_2) ]
                 | (int_expr >> ">"  >> int_expr) [ _val = ph::bind(&make_cmp_op, &op_greater,    qi::_1, qi::_2) ]
                 | (int_expr >> ">=" >> int_expr) [ _val = ph::bind(&make_cmp_op, &op_greater_eq, qi::_1, qi::_2) ]
                 | (int_expr >> "==" >> int_expr) [ _val = ph::bind(&make_cmp_op, &op_eq,         qi::_1, qi::_2) ]
                 | (int_expr >> "!=" >> int_expr) [ _val = ph::bind(&make_cmp_op, &op_not_eq,     qi::_1, qi::_2) ];
        int_expr = int_prop  [ _val = qi::_1 ]
                 | int_const [ _val = ph::bind(&make_const<int>, qi::_1) ];
        int_const = int_ [ _val = qi::_1 ];
        int_prop = identifier [ _val = ph::bind(&make_prop_reader<int>, qi::_1, _pass) ];
    }

    qi::rule<I, std::string(), S> identifier;
    qi::rule<I, int(), S> int_const;
    qi::rule<I, int_func(), S> int_expr, int_prop;
    qi::rule<I, bool_func(), S> bool_expr, bool_expr2, bool_expr3, int_comp, bool_prop;
};

boost::function<bool (const object &)> parse(const std::string &src) {
    if (src.empty())
        return make_const<bool>(true);
    bool_func p;
    std::string::const_iterator b = src.begin(), e = src.end();
    predicate_grammar<std::string::const_iterator, boost::spirit::ascii::space_type> grammar;
    if (!qi::phrase_parse(b, e, grammar, boost::spirit::ascii::space, p) || b != e) {
        std::stringstream s;
        s << "Predicate parsing failed at " << (b - src.begin()) << " in \"" << src << "\"";
        throw std::runtime_error(s.str());
    }
    return p;
}
}

using predicate::properties;
using predicate::parse;

void show(const std::string& st,bool a){
  predicate::object obj;    
  assert(parse(st)(obj) == a);
}

int main(){
    
    properties<int>::create("less_val",10);
    properties<int>::create("greater_val",11);
    properties<bool>::create("tr_val",true);
    properties<bool>::create("fls_val",false);
    
   
    show("tr_val",true);
    show("fls_val",false);
    show("less_val < greater_val",true);
    show("(less_val > greater_val) || tr_val",true);
    show("(greater_val < less_val)",false);
    show("tr_val && fls_val",false);
    show("tr_val && !fls_val",true);
    show("!(greater_val == less_val)",true);
    show("!(tr_val && fls_val)",true);
    return 0;
}