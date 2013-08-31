//#define BOOST_SPIRIT_DEBUG
#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/variant/recursive_wrapper.hpp>
#include <boost/lexical_cast.hpp>

namespace qi    = boost::spirit::qi;
namespace karma = boost::spirit::karma;
namespace phx   = boost::phoenix;

typedef boost::variant<int, std::string> value;
typedef boost::variant<value, boost::recursive_wrapper<struct function_call> > expr;

typedef std::function<value()                          > nullary_function_impl;
typedef std::function<value(value const&)              > unary_function_impl;
typedef std::function<value(value const&, value const&)> binary_function_impl;

typedef boost::variant<nullary_function_impl, unary_function_impl, binary_function_impl> function_impl;
typedef qi::symbols<char, function_impl> function_table;

struct function_call 
{ 
    typedef std::vector<expr> arguments_t;
    function_call() = default;

    function_call(function_impl f, arguments_t const& arguments) 
        : f(f), arguments(arguments) { }

    function_impl f;
    arguments_t arguments;

};

BOOST_FUSION_ADAPT_STRUCT(function_call, (function_impl, f)(function_call::arguments_t, arguments))

#ifdef BOOST_SPIRIT_DEBUG
namespace std
{
    static inline std::ostream& operator<<(std::ostream& os, nullary_function_impl const& f) { return os << "<nullary_function_impl>"; }
    static inline std::ostream& operator<<(std::ostream& os, unary_function_impl const& f)   { return os << "<unary_function_impl>";   }
    static inline std::ostream& operator<<(std::ostream& os, binary_function_impl const& f)  { return os << "<binary_function_impl>";  }
}
static inline std::ostream& operator<<(std::ostream& os, function_call const& call) { return os << call.f << "(" << call.arguments.size() << ")"; }
#endif

//////////////////////////////////////////////////
// Evaluation
struct eval : boost::static_visitor<value> 
{
    eval() {}

    value operator()(const value& v) const 
    { 
        return v;
    }

    value operator()(const function_call& call) const
    {
        switch(call.arguments.size())
        {
            case 0: {
                    return boost::get<nullary_function_impl>(call.f)();
                }
            case 1: {
                    auto a = recurse(call.arguments[0]);
                    return boost::get<unary_function_impl>(call.f)(a);
                }
            case 2: {
                    auto a = recurse(call.arguments[0]);
                    auto b = recurse(call.arguments[1]);
                    return boost::get<binary_function_impl>(call.f)(a, b);
                }
            default:
                throw "Not implemented";
        }
    }

  private:
    template<typename T>
    value recurse(T const& v) const { return boost::apply_visitor(*this, v); }
};

value evaluate(const expr& e)
{ 
    return boost::apply_visitor(eval(), e); 
}

//////////////////////////////////////////////////
// Demo functions:
value AnswerToLTUAE() {
    return 42;
}

value ReverseString(value const& input) {
    auto& as_string = boost::get<std::string>(input);
    return std::string(as_string.rbegin(), as_string.rend());
}

value Concatenate(value const& a, value const& b) {
    std::ostringstream oss;
    oss << a << b;
    return oss.str();
}

//////////////////////////////////////////////////
// Parser grammar
template <typename It, typename Skipper = qi::space_type>
    struct parser : qi::grammar<It, expr(), Skipper>
{
    parser() : parser::base_type(expr_)
    {
        using namespace qi;

        n_ary_ops.add
            ("AnswerToLTUAE", nullary_function_impl{ &::AnswerToLTUAE })
            ("ReverseString", unary_function_impl  { &::ReverseString })
            ("Concatenate"  , binary_function_impl { &::Concatenate });
        
        function_call_ = n_ary_ops > '(' > expr_list > ')';
        string_        = qi::lexeme [ "'" >> *~qi::char_("'") >> "'" ];
        value_         = qi::int_ | string_;

        expr_list      = -expr_ % ',';
        expr_          = function_call_ | value_;

        on_error<fail> ( expr_, std::cout
             << phx::val("Error! Expecting ") << _4 << phx::val(" here: \"")
             << phx::construct<std::string>(_3, _2) << phx::val("\"\n"));

        BOOST_SPIRIT_DEBUG_NODES((expr_)(expr_list)(function_call_)(value_)(string_))
    }

  private:
    function_table          n_ary_ops;

    template <typename Attr> using Rule = qi::rule<It, Attr(), Skipper>;
    Rule<std::string>       string_;
    Rule<value>             value_;
    Rule<function_call>     function_call_;
    Rule<std::vector<expr>> expr_list;
    Rule<expr>              expr_;
};

//////////////////////////////////////////////////
// Output generator
template <typename It>
    struct generator : karma::grammar<It, expr()>
{
    generator() : generator::base_type(expr_)
    {
        using namespace karma;

        nullary_       = eps << "nullary_function_call";              // TODO reverse lookup :)
        unary_         = eps << "unary_function_call";
        binary_        = eps << "binary_function_call";

        function_      = nullary_ | unary_ | binary_;
        function_call_ = function_ << expr_list;

        expr_list      = '(' << -(expr_ % ',') << ')';
        value_         = karma::int_ | ("'" << karma::string << "'");
        expr_          = function_call_ | value_;
    }

  private:
    template <typename Attr> using Rule = karma::rule<It, Attr()>;
    Rule<nullary_function_impl> nullary_;
    Rule<unary_function_impl>   unary_;
    Rule<binary_function_impl>  binary_;
    Rule<function_impl>         function_;
    Rule<function_call>         function_call_;
    Rule<value>                 value_;
    Rule<std::vector<expr>>     expr_list;
    Rule<expr>                  expr_;
};

int main()
{
    for (const std::string input: std::vector<std::string> { 
            "-99",
            "'string'",
            "AnswerToLTUAE()",
            "ReverseString('string')",
            "Concatenate('string', 987)",
            })
    {
        auto f(std::begin(input)), l(std::end(input));
        const static parser<decltype(f)> p;

        expr result;
        bool ok = qi::phrase_parse(f,l,p,qi::space,result);

        if (!ok)
            std::cout << "invalid input\n";
        else
        {
            const static generator<boost::spirit::ostream_iterator> g;
            std::cout << "tree: " << karma::format(g, result) << "\n";
            std::cout << "eval: " << evaluate(result) << "\n";
        }

        if (f!=l) std::cout << "unparsed: '" << std::string(f,l) << "'\n";
    }
}
