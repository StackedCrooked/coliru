#define BOOST_SPIRIT_USE_PHOENIX_V3
#define BOOST_SPIRIT_DEBUG
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/phoenix/function/adapt_function.hpp>
#include <boost/lexical_cast.hpp>

namespace qi   = boost::spirit::qi;
namespace phx  = boost::phoenix;

typedef boost::variant<int, double>               NumValue;
typedef boost::variant<int, double, std::wstring> GenericValue;

struct InvalidParamEx : public virtual std::exception 
{
    const char* what() const noexcept { return "Invalid type of operand/parameter"; }
};

struct AsNumValue : boost::static_visitor<NumValue>
{
    int      operator()(int i)                 const { return i; }
    double   operator()(double d)              const { return d; }
    NumValue operator()(std::wstring const& s) const
    { 
        try { return boost::lexical_cast<int>(s); }    catch(...) {}
        try { return boost::lexical_cast<double>(s); } catch(...) {}
        throw InvalidParamEx();
    }
};

struct CTranslationFunctions
{
    static GenericValue GetSubString(GenericValue const& str, GenericValue position, GenericValue len);
    static GenericValue ConcatenateStrings(GenericValue const& a, GenericValue const& b);

  private: // helper
    NumValue static num(GenericValue const& v) { return boost::apply_visitor(AsNumValue(), v); }

#define DEFUNOP(name, expr) private: struct do_##name : boost::static_visitor<NumValue> \
    {                                                                               \
        template <typename T1> auto operator()(T1 const& a) const -> decltype(expr) \
        { return expr; }                                                            \
    }; \
    public: static NumValue name(GenericValue const& a) { auto na=num(a); return boost::apply_visitor(do_##name(), na); }
#define DEFBINOP(name, infix) struct do_##name : boost::static_visitor<NumValue>                \
    {                                                                                       \
        template <typename T1, typename T2> auto operator()(T1 const& a, T2 const& b) const \
         -> decltype(a infix b)                                                             \
        { return a infix b; }                                                               \
    }; \
    public: static NumValue name(GenericValue const& a, GenericValue const& b) { auto na=num(a), nb=num(b); return boost::apply_visitor(do_##name(), na, nb); }

    // define the operators polymorphically, so `int` + `double` becomes `double`, but `int` * `int` stays `int`
    DEFBINOP(Add     , +);
    DEFBINOP(Subtruct, -);
    DEFBINOP(Multiply, *);
    DEFBINOP(Divide  , /);
    DEFUNOP (Negate  , -a);
    DEFUNOP (Sqrt    , sqrt(a));
};

GenericValue CTranslationFunctions::GetSubString(GenericValue const& str, GenericValue position, GenericValue len)
{
    using boost::get;
    return get<std::wstring>(str).substr(get<int>(position), get<int>(len));
}

GenericValue CTranslationFunctions::ConcatenateStrings(GenericValue const& a, GenericValue const& b) 
{
    std::wostringstream woss;
    woss << a << b;
    return woss.str();
}

BOOST_PHOENIX_ADAPT_FUNCTION(GenericValue, ConcatenateStrings_, CTranslationFunctions::ConcatenateStrings, 2)
BOOST_PHOENIX_ADAPT_FUNCTION(GenericValue, GetSubString_      , CTranslationFunctions::GetSubString      , 3)

BOOST_PHOENIX_ADAPT_FUNCTION(NumValue    , Add_               , CTranslationFunctions::Add               , 2)
BOOST_PHOENIX_ADAPT_FUNCTION(NumValue    , Subtruct_          , CTranslationFunctions::Subtruct          , 2)
BOOST_PHOENIX_ADAPT_FUNCTION(NumValue    , Multiply_          , CTranslationFunctions::Multiply          , 2)
BOOST_PHOENIX_ADAPT_FUNCTION(NumValue    , Divide_            , CTranslationFunctions::Divide            , 2)
BOOST_PHOENIX_ADAPT_FUNCTION(NumValue    , Negate_            , CTranslationFunctions::Negate            , 1)
BOOST_PHOENIX_ADAPT_FUNCTION(NumValue    , Sqrt_              , CTranslationFunctions::Sqrt              , 1)

// Grammar to parse map functions
template <typename It, typename Skipper = qi::space_type >
struct MapFunctionParser : qi::grammar<It, GenericValue(), Skipper>
{
    MapFunctionParser() : MapFunctionParser::base_type(expr_)
    {
        using namespace qi;

        function_call_ = 
          (no_case["GetSubString"]       > '(' > expr_ > ',' > expr_ > ',' > expr_ > ')') [ _val = GetSubString_(_1, _2, _3)   ]
        | (no_case["ConcatenateStrings"] > '(' > expr_ > ',' > expr_ > ')')               [ _val = ConcatenateStrings_(_1, _2) ]
        | (no_case["Sqrt"]               > '(' > expr_ > ')')                             [ _val = Sqrt_(_1)                   ]
        ;

        string_ = // keep it simple, silly (KISS)
            (L'"' > *~char_('"') > L'"')
          | (L"'" > *~char_("'") > L"'");  
            
        arithmeticexpression_ =
            term_                  [ _val = _1                  ]
        >>  *( ('+' >> term_       [ _val = Add_(_val,_1)       ])
             | ('-' >> term_       [ _val = Subtruct_(_val, _1) ])
             );                      
                                     
        term_ =                      
              factor_              [ _val = _1                  ]
            >> *( ('*' >> factor_  [ _val = Multiply_(_val, _1) ])
                | ('/' >> factor_  [ _val = Divide_(_val, _1)   ])
                );

        factor_ =
                int_               [ _val = _1          ]
            |   double_            [ _val = _1          ]
            |   string_            [ _val = _1          ]
            |   ('-' >> factor_)   [ _val = Negate_(_1) ]
            |   ('+' >> factor_)   [ _val = _1          ]
            |   function_call_     [ _val = _1          ]
            ;

        expr_ = arithmeticexpression_;

        on_error<fail> ( expr_, std::cout
            << phx::val("Error! Expecting ") << _4 << phx::val(" here: \"")
            << phx::construct<std::string>(_3, _2) << phx::val("\"\n"));

        BOOST_SPIRIT_DEBUG_NODE(function_call_);
        BOOST_SPIRIT_DEBUG_NODE(expr_);
        BOOST_SPIRIT_DEBUG_NODE(string_);
        BOOST_SPIRIT_DEBUG_NODE(funcparameter_);
        BOOST_SPIRIT_DEBUG_NODE(arithmeticexpression_);
        BOOST_SPIRIT_DEBUG_NODE(factor_);
        BOOST_SPIRIT_DEBUG_NODE(term_);
    }

private:
    qi::rule<It, std::wstring()> 
        string_; // NO SKIPPER (review)
    qi::rule<It, GenericValue(), Skipper> 
        function_call_, expr_, funcparameter_, // NO LOCALS (review)
        arithmeticexpression_, term_, factor_;
};

int main()
{
    static const MapFunctionParser<std::wstring::const_iterator> p;

    std::wstring input;
    while (std::getline(std::wcin, input))
    {
        std::wstring::const_iterator f(begin(input)), l(end(input));

        GenericValue value;
        assert(qi::phrase_parse(f, l, p, qi::space, value));

        if (f!=l)
            std::wcout << L"remaining unparsed: '" << std::wstring(f,l) << L"'\n";

        std::wcout << input << " --> " << value;
    }
}
