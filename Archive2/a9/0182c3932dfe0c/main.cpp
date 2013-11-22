#include <boost/spirit/include/qi.hpp>

using namespace boost::spirit::qi;

using A  = boost::variant<int, double>;
static real_parser<double, strict_real_policies<double>> const strict_double;

A parse(std::string const& s)
{
    auto f(begin(s)), l(end(s));
    static rule<decltype(f), A()> const p = strict_double | int_;
    
    A a;
    assert(parse(f,l,p,a));

    return a;
}

int main()
{
    assert(0 == parse("42").which());
    assert(0 == parse("-42").which());
    assert(0 == parse("+42").which());

    assert(1 == parse("42.").which());
    assert(1 == parse("0.").which());
    assert(1 == parse(".0").which());
    assert(1 == parse("0.0").which());
    assert(1 == parse("1e1").which());
    assert(1 == parse("1e+1").which());
    assert(1 == parse("1e-1").which());
    assert(1 == parse("-1e1").which());
    assert(1 == parse("-1e+1").which());
    assert(1 == parse("-1e-1").which());
}
