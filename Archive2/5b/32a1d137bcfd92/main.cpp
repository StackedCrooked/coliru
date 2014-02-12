#include <iostream>

struct Context {}; // stub

struct IRule
{
    virtual ~IRule() {}
    virtual void Begin(int value) = 0;
    virtual double Evaluate(Context& context) = 0;
};

#include <tuple>
#include <boost/fusion/adapted/std_tuple.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <boost/fusion/include/accumulate.hpp>
#include <boost/phoenix.hpp>

namespace phx = boost::phoenix;
namespace fus = boost::fusion;
using namespace phx::arg_names;

template<typename... R>
class CompositeRule : public IRule
{
    std::tuple<R...> m_rules;
  public:
    CompositeRule(R... rules) : m_rules(rules...) {}

public:
    virtual void Begin(int value)
    {
        fus::for_each(m_rules, phx::bind(&IRule::Begin, arg1, value));
    }

    virtual double Evaluate(Context& context)
    {
        return fus::accumulate(m_rules, 0.0, arg1 + phx::bind(&IRule::Evaluate, arg2, phx::ref(context)));
    }
};


template<typename... R>
CompositeRule<R...> make_composite(R&&... rules)
{
    return CompositeRule<R...>(std::forward<R>(rules)...);
}

void DoSomething(IRule *rule)
{
    static Context ctx;

    rule->Begin(2);
    std::cout << "Sum of Evaluate: " << rule->Evaluate(ctx) << "\n";
}

struct RuleA : IRule { /* concrete implementation */
    RuleA(double v = 3.14) : _val(v), _x(0) {} double _val, _x; 
    void Begin(int x)                 { /*std::cout << __PRETTY_FUNCTION__ << "\n";*/ _x = x;         }
    double Evaluate(Context& context) { /*std::cout << __PRETTY_FUNCTION__ << "\n";*/ return _val*_x; }
};

int main()
{
    auto combine(make_composite(RuleA(20), RuleA(), RuleA(100)));

    DoSomething(&combine);

    // you can even re-compose:
    auto more(make_composite(combine, RuleA(-200), combine, combine, combine));
    DoSomething(&more);
}
