#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/lexical_cast.hpp>

namespace qi    = boost::spirit::qi;
namespace phx   = boost::phoenix;

typedef boost::function<double()> Value;

#define BINARY_FUNCTOR(name, op)                        \
    struct name                                         \
    {                                                   \
        name(Value x, Value y): x_(x), y_(y) {}         \
        double operator()() { return x_() op y_(); }    \
        Value x_, y_;                                   \
    };

BINARY_FUNCTOR(ADD, +)
BINARY_FUNCTOR(SUB, -)
BINARY_FUNCTOR(MUL, *)
BINARY_FUNCTOR(DIV, /)

struct LIT
{
    LIT(double x): x_(x) {}
    double operator()()
    {
        return x_;
    }
    double x_;
};

struct NEG
{
    NEG(Value x): x_(x) {}
    double operator()()
    {
        return -x_();
    }
    Value x_;
};

struct SQRT
{
    SQRT(Value x): x_(x) {}
    double operator()()
    {
        return sqrt(x_());
    }
    Value x_;
};

// expression grammar definition
template <typename It, typename Skipper=qi::space_type>
struct parser : qi::grammar<It, Value(),  Skipper>
{
    parser() : parser::base_type(expression)
    {
        using namespace qi;
        expression =
            term                    [_val = _1]
            >> *(('+' >> term       [_val = phx::construct<ADD>(_val, _1)])
                    | ('-' >> term  [_val = phx::construct<SUB>(_val, _1)])
                );
        term =
            factor                  [_val = _1]
            >> *(('*' >> factor     [_val = phx::construct<MUL>(_val, _1)])
                 | ('/' >> factor   [_val = phx::construct<DIV>(_val, _1)])
                );
        factor =
            double_                 [_val = phx::construct<LIT>(_1)]
            | '(' >> expression [_val = _1] >> ')'
            | ('-' >> factor        [_val = phx::construct<NEG>(_1)])
            | ('+' >> factor        [_val = _1])
            | (string("SQRT") >> '(' >> expression [_val = phx::construct<SQRT>(_1)] >> ')');
        
        BOOST_SPIRIT_DEBUG_NODE(expression);
        BOOST_SPIRIT_DEBUG_NODE(term);
        BOOST_SPIRIT_DEBUG_NODE(factor);
    }

    private:
    qi::rule<It, std::wstring(), Skipper> scientificNumber;
    qi::rule<It, Value(), Skipper> expression, term, factor;

};



int main()
{
    const std::wstring testExp = L"3E-10*(12-3)";

    typedef std::wstring::const_iterator It;
    It f(testExp.begin()), e(testExp.end());
    parser<It, qi::space_type> expressionParser;

    Value logicExpression;
    bool ok = phrase_parse(f,e,expressionParser,qi::space,logicExpression);

    std::cout << "Success: " << std::boolalpha << ok << "\tValue: " << logicExpression() << '\n';
}
